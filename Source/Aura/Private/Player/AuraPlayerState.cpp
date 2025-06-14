#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraPlayerState)

AAuraPlayerState::AAuraPlayerState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UAuraAbilitySystemComponent>(NAME_AbilitySystemComponent))
{
    GetAbilitySystemComponentFast()->SetIsReplicated(true);
    GetAbilitySystemComponentFast()->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

    // This is quite a high update frequency. Perhaps we should lower it in the final game
    SetNetUpdateFrequency(100.f);
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Level);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
    // Unclear why we don't just remove this method...
}
