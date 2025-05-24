#include "Input/AuraInputConfig.h"
#include "InputAction.h"
#include "Logging/StructuredLog.h"
#include "Misc/DataValidation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraInputConfig)

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
                                                                   bool bLogNotFound) const
{
    // ReSharper disable once CppUseStructuredBinding
    for (const auto& Action : Actions)
    {
        if (Action.InputTag.MatchesTagExact(InputTag))
        {
            return Action.InputAction;
        }
    }
    if (bLogNotFound)
    {
        UE_LOGFMT(LogTemp,
                  Error,
                  "Unable to locate InputAction for Tag {InputTag} in InputConfig {InputConfig}",
                  *InputTag.ToString(),
                  *GetNameSafe(this));
    }

    return nullptr;
}

#if WITH_EDITOR
EDataValidationResult UAuraInputConfig::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        if (Actions.IsEmpty())
        {
            const auto String =
                FString::Printf(TEXT("Object %s is not an abstract class and has not defined any actions."),
                                *GetName());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }
    int Index = 0;
    // ReSharper disable once CppUseStructuredBinding
    for (const auto& Action : Actions)
    {
        if (!Action.InputTag.IsValid())
        {
            const auto String =
                FString::Printf(TEXT("Object %s has an invalid property Actions[%d].InputTag"), *GetName(), Index);
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        if (!IsValid(Action.InputAction))
        {
            const auto String =
                FString::Printf(TEXT("Object %s has an invalid property Actions[%d].InputAction"), *GetName(), Index);
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        Index++;
    }

    return Result;
}
#endif
