#include "VaaliStatsComponent.h"

//FStatAttribute implementations
void FStatAttribute::Increase(float Amount)
{
    if (Amount <= 0) return;
    CurrentValue = FMath::Clamp(CurrentValue + Amount, 0.f, MaxValue);
}

void FStatAttribute::Decrease(float Amount)
{
    if (Amount <= 0) return;
    CurrentValue = FMath::Clamp(CurrentValue - Amount, 0.f, MaxValue);
}

float FStatAttribute::GetNormalized() const
{
    return CurrentValue/MaxValue;
}

bool FStatAttribute::IsEmpty() const
{
    return CurrentValue <= 0;
}

// UVaaliStatsComponents implementations
UVaaliStatsComponent::UVaaliStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UVaaliStatsComponent::BeginPlay()
{
    Super::BeginPlay();
    
    // expose stat for designer to set value
    Health.CurrentValue = FMath::Clamp(Health.CurrentValue, 0.f, Health.MaxValue);
    Stamina.CurrentValue = FMath::Clamp(Stamina.CurrentValue, 0.f, Stamina.MaxValue);
    Honor.CurrentValue = FMath::Clamp(Honor.CurrentValue, 0.f, Honor.MaxValue);
}

void UVaaliStatsComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    // RecoverStamina(DeltaTime);
}

void UVaaliStatsComponent::ApplyDamage(float Amount)
{
    Health.Decrease(Amount);
}

void UVaaliStatsComponent::RestoreHealth(float Amount)
{
    Health.Increase(Amount);
}

void UVaaliStatsComponent::DrainStamina(float Amount)
{
    // TODO: Once the sprint logic is implemented
}

void UVaaliStatsComponent::RecoverStamina(float Amount)
{
    // TODO: Once the sprint logic is implemented
}

bool UVaaliStatsComponent::HasEnoughStamina(float Amount) const
{
    return Stamina.CurrentValue >= Amount;
}

void UVaaliStatsComponent::AddHonor(float Amount)
{
    Honor.Increase(Amount);
}

bool UVaaliStatsComponent::SpendHonor(float Amount)
{
    if (Honor.CurrentValue < Amount) return false;
    Honor.Decrease(Amount);
    return true;
}
