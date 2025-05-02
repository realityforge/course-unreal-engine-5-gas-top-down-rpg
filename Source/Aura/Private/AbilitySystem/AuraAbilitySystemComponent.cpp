#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::OnEffectApplied);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void UAuraAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                  const FGameplayEffectSpec& GameplayEffectSpec,
                                                  FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
    FGameplayTagContainer Tags;
    GameplayEffectSpec.GetAllAssetTags(Tags);

    for (const auto& Tag : Tags)
    {
        // TODO: Broadcast tag to widget controller
    }
}
