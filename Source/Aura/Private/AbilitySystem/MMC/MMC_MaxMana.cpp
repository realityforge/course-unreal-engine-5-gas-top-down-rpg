#include "AbilitySystem/MMC/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
    // Here we set up all the captures we will require in the Calculate method.

    IntelligenceAttributeCapture.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
    IntelligenceAttributeCapture.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    // Should we capture the attribute when the EffectSpec is created (bSnapshot = false) or
    // when the EffectSpec is applied (bSnapshot = true). In this case they occur at the same
    // time so it does not matter too much.
    IntelligenceAttributeCapture.bSnapshot = false;

    RelevantAttributesToCapture.Add(IntelligenceAttributeCapture);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    // This is where we get the value of all captured attributes
    float Intelligence = 0.f;
    GetCapturedAttributeMagnitude(IntelligenceAttributeCapture, Spec, EvaluationParameters, Intelligence);
    Intelligence = FMath::Max<float>(Intelligence, 0.f);

    // The SourceObject is the object that this effect was created from
    const auto SourceObject = Spec.GetContext().GetSourceObject();
    const auto CombatInterface = Cast<ICombatInterface>(SourceObject);
    const auto PlayerLevel = ensure(CombatInterface) ? CombatInterface->GetPlayerLevel() : 0;

    // Some arbitrary calculation to derive the BaseMagnitude
    return 50.f + 2.5f * Intelligence + 15.f * PlayerLevel;
}
