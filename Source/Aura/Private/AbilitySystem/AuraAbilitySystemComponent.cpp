#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::OnEffectApplied);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void UAuraAbilitySystemComponent::OnEffectApplied(
    [[maybe_unused]] UAbilitySystemComponent* AbilitySystemComponent,
    const FGameplayEffectSpec& GameplayEffectSpec,
    [[maybe_unused]] FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
    FGameplayTagContainer Tags;
    GameplayEffectSpec.GetAllAssetTags(Tags);
    EffectAssetTags.Broadcast(Tags);
}
