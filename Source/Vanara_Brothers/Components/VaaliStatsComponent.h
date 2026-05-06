#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VaaliStatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FStatAttribute
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentValue;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxValue;
    
    FStatAttribute() : CurrentValue(100.f), MaxValue(100.f) {}
    
    void Increase(float Amount);
    void Decrease(float Amount);
    float GetNormalized() const;
    bool IsEmpty() const;
};

UCLASS(ClassGroup= (Custom), meta = (BlueprintSpawnableComponent))
class VANARA_BROTHERS_API UVaaliStatsComponent: public UActorComponent
{
    GENERATED_BODY()
    
public:
    UVaaliStatsComponent();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStatAttribute Health;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStatAttribute Stamina;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FStatAttribute Honor;
    
    // Health
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ApplyDamage(float Amount);
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void RestoreHealth(float Amount);
    
    // Stamina
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void DrainStamina(float Amount);
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool HasEnoughStamina(float Amount) const;
    
    // Honor
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddHonor(float Amount);
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool SpendHonor(float Amount);
    
protected:
    virtual void BeginPlay() override;
    
private:
    void RecoverStamina(float DeltaTime);
    
public:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};