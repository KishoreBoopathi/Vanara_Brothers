#include "VaaliCharacter.h"
#include "VaaliStatsComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AVaaliCharacter::AVaaliCharacter()
{
     PrimaryActorTick.bCanEverTick = true;
     
     // Spring Arm setup
     CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
     CameraBoom->SetupAttachment(RootComponent);
     CameraBoom->TargetArmLength = 400.f;
     CameraBoom->bUsePawnControlRotation = true;
     
     // Camera Setup
     FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
     FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
     FollowCamera->bUsePawnControlRotation = false;
     
     // Stats Component
     StatsComponent = CreateDefaultSubobject<UVaaliStatsComponent>(TEXT("StatsComponent"));
     
     // Character Movement setup
     GetCharacterMovement()->bOrientRotationToMovement = true;
     GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
     GetCharacterMovement()->MaxWalkSpeed = 500.f;
     GetCharacterMovement()->JumpZVelocity = 700.f;
     GetCharacterMovement()->AirControl = 0.35f;
     
     // Don't rotate character with camera
     bUseControllerRotationPitch = false;
     bUseControllerRotationYaw = false;
     bUseControllerRotationRoll = false;
}

void AVaaliCharacter::BeginPlay()
{
     Super::BeginPlay();
     
     // Add Input Mapping Context
     if (APlayerController *PC = Cast<APlayerController>(GetController()))
     {
          if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
               ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
          {
               Subsystem->AddMappingContext(DefaultMappingContext, 0);
          }
     }
}

void AVaaliCharacter::Tick( float DeltaTime )
{
     Super::Tick( DeltaTime );
}

void AVaaliCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
     Super::SetupPlayerInputComponent(PlayerInputComponent);
     
     if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
     {
          EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVaaliCharacter::Move);
          EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVaaliCharacter::Look);
          EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
          EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
          EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &AVaaliCharacter::SprintStart);
          EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &AVaaliCharacter::SprintEnd);
          EIC->BindAction(DodgeAction, ETriggerEvent::Started, this, &AVaaliCharacter::Dodge);
          EIC->BindAction(LightAttackAction, ETriggerEvent::Started, this, &AVaaliCharacter::LightAttack);
     }
}

void AVaaliCharacter::Move(const FInputActionValue& Value)
{
     FVector2D MovementVector = Value.Get<FVector2D>();
     
     if (Controller != nullptr)
     {
          const FRotator Rotation = Controller->GetControlRotation();
          const FRotator YawRotation(0, Rotation.Yaw, 0);
          
          const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
          const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
          
          AddMovementInput(ForwardDirection, MovementVector.Y);
          AddMovementInput(RightDirection, MovementVector.X);
     }
}

void AVaaliCharacter::Look(const FInputActionValue& Value)
{
     FVector2D LookAxisVector = Value.Get<FVector2D>();
     
     if (Controller != nullptr)
     {
          AddControllerYawInput(LookAxisVector.X);
          AddControllerPitchInput(-LookAxisVector.Y);
     }
}

void AVaaliCharacter::SprintStart()
{
     GetCharacterMovement()->MaxWalkSpeed = 900.f;
}

void AVaaliCharacter::SprintEnd()
{
     GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void AVaaliCharacter::Dodge()
{
     // TODO: Implement dodge roll with animation montage
}

void AVaaliCharacter::LightAttack()
{
     UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
     if (AnimInstance && LightAttackMontage)
     {
          AnimInstance->Montage_Play(LightAttackMontage, 1.f);
     }
}
     
