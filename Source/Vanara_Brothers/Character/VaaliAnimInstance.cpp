#include "VaaliAnimInstance.h"
#include "VaaliCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UVaaliAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	VaaliCharacter = Cast<AVaaliCharacter>(TryGetPawnOwner());
}

void UVaaliAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (VaaliCharacter == nullptr)
	{
		VaaliCharacter = Cast<AVaaliCharacter>(TryGetPawnOwner());
		return;
	}
	
	// Ground speed - overall lateral speed for state transitions
	FVector Velocity = VaaliCharacter->GetVelocity();
	Velocity.Z = 0.f;
	GroundSpeed = Velocity.Size();
	
	// Local velocity for 2D blend space
	FVector LocalVelocity = VaaliCharacter->GetActorTransform()
							.InverseTransformVector(VaaliCharacter->GetVelocity());
	VelocityX = LocalVelocity.Y;
	VelocityY = LocalVelocity.X;
	
	// Air state
	bIsInAir = VaaliCharacter->GetCharacterMovement()->IsFalling();
	
	// Accelerating - is player pressing movement input
	bIsAccelerating = VaaliCharacter->GetCharacterMovement()
						->GetCurrentAcceleration().Size() > 0.f;
	
	// Sprint - check if speed exceeds walk threshold
	bIsSprinting = GroundSpeed > 600.f;
}
