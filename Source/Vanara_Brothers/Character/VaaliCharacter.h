#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VaaliCharacter.generated.h"

//Forward Declarations
class USpringArmComponent;
class UCameraComponent;
class UVaaliStatsComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class VANARA_BROTHERS_API AVaaliCharacter : public ACharacter
{
    GENERATED_BODY()
    
public:
    AVaaliCharacter();
    
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> FollowCamera;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
    TObjectPtr<UVaaliStatsComponent> StatsComponent;
    
    // Input Actions
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> LookAction;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> JumpAction;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> SprintAction;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> DodgeAction;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> LightAttackAction;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    TObjectPtr<UAnimMontage> LightAttackMontage;
    
protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    // Input Callbacks
    void Move(const struct FInputActionValue& Value);
    void Look(const struct FInputActionValue& Value);
    void SprintStart();
    void SprintEnd();
    void Dodge();
    void LightAttack();
    
public:
    virtual void Tick(float DeltaTime) override;
};