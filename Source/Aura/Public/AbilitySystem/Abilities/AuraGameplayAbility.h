#pragma once

#include "Aeon/AbilitySystem/AeonGameplayAbility.h"
#include "CoreMinimal.h"
#include "AuraGameplayAbility.generated.h"

/**
 * The base GameplayAbility class used by Aura.
 */
UCLASS(Abstract)
class AURA_API UAuraGameplayAbility : public UAeonGameplayAbility
{
    GENERATED_BODY()
};
