#pragma once

#include "Aeon/AbilitySystem/AeonAbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature, const FGameplayTagContainer& /*AssetTags*/);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAeonAbilitySystemComponent
{
    GENERATED_BODY()

public:
    /**
     * Invoked when the ability actor information has been set and initialized.
     * This method provides a hook to execute custom behavior or logic after
     * the actor's ability system component has been fully initialized with the
     * associated actor info.
     *
     * Common scenarios for this method may include:
     * - Setting up additional state or logic that relies on a fully initialized
     *   AbilityActorInfo.
     * - Extending base behavior for custom gameplay needs specific to derived
     *   implementations.
     *
     * This function must be explicitly called after the ability system component
     * has been initialized, as seen in setups such as character or enemy
     * initialization routines.
     */
    void AbilityActorInfoSet();

    FEffectAssetTagsSignature EffectAssetTags;

protected:
    UFUNCTION(Client, Reliable)
    void ClientOnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                               const FGameplayEffectSpec& GameplayEffectSpec,
                               FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
