#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
    // Here we set up all the captures we will require in the Calculate method.

    VigorAttributeCapture.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
    VigorAttributeCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    // Should we capture the attribute when the EffectSpec is created (bSnapshot = false) or
    // when the EffectSpec is applied (bSnapshot = true). In this case they occur at the same
    // time so it does not matter too much.
    VigorAttributeCapture.bSnapshot = false;

    RelevantAttributesToCapture.Add(VigorAttributeCapture);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    // This is where we get the value of all captured attributes
    float Vigor = 0.f;
    GetCapturedAttributeMagnitude(VigorAttributeCapture, Spec, EvaluationParameters, Vigor);
    Vigor = FMath::Max<float>(Vigor, 0.f);

    // The SourceObject is the object that this effect was created from
    const auto SourceObject = Spec.GetContext().GetSourceObject();
    const auto CombatInterface = Cast<ICombatInterface>(SourceObject);
    const auto PlayerLevel = ensure(CombatInterface) ? CombatInterface->GetPlayerLevel() : 0;

    // Some arbitrary calculation to derive the BaseMagnitude
    return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
