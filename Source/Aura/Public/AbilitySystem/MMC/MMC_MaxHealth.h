#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

UCLASS()
// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
    GENERATED_BODY()

public:
    // ReSharper disable once IdentifierTypo
    UMMC_MaxHealth();

    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
    FGameplayEffectAttributeCaptureDefinition VigorAttributeCapture;
};
