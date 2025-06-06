#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAbilitySystemComponent)

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
    // On server when effect is applied, broadcast call to client
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientOnEffectApplied);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAbilitySystemComponent::ClientOnEffectApplied_Implementation(
    [[maybe_unused]] UAbilitySystemComponent* AbilitySystemComponent,
    const FGameplayEffectSpec& GameplayEffectSpec,
    [[maybe_unused]] FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
    FGameplayTagContainer Tags;
    GameplayEffectSpec.GetAllAssetTags(Tags);
    EffectAssetTags.Broadcast(Tags);
}
