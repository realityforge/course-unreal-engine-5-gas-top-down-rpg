#include "AbilitySystem/Data/AttributeInfo.h"
#include "Logging/StructuredLog.h"
#include "Misc/DataValidation.h"

bool FAuraAttributeDef::IsValid() const
{
    return Tag.IsValid() && !Name.IsEmpty();
}

FAuraAttributeDef UAttributeInfo::FindAttributeDefForTag(const FGameplayTag& AttributeTag,
                                                         const bool bLogNotFound) const
{
    for (const auto& Info : Attributes)
    {
        if (Info.Tag.MatchesTagExact(AttributeTag))
        {
            return Info;
        }
    }

    if (bLogNotFound)
    {
        UE_LOGFMT(LogTemp,
                  Error,
                  "UAttributeInfo::FindAttributeInfoForTag() -"
                  " Can't find Info for AttributeTag [{Tag}] on AttributeInfo [{Info}].",
                  AttributeTag.GetTagName(),
                  GetName());
    }

    return FAuraAttributeDef();
}

#if WITH_EDITOR
EDataValidationResult UAttributeInfo::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        if (0 == Attributes.Num())
        {
            const auto String =
                FString::Printf(TEXT("Object %s is not abstract but has specified 0 AttributeInformation values"),
                                *GetName());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        else
        {
            int32 Index = 0;
            // ReSharper disable once CppUseStructuredBinding
            for (auto AttributeInfo : Attributes)
            {
                if (AttributeInfo.Tag.ToString().IsEmpty())
                {
                    const auto String =
                        FString::Printf(TEXT("Object %s is not abstract but AttributeInformation[%d].Tag is empty."),
                                        *GetName(),
                                        Index);
                    Context.AddError(FText::FromString(String));
                    Result = EDataValidationResult::Invalid;
                }
                if (AttributeInfo.Name.ToString().IsEmpty())
                {
                    const auto String =
                        FString::Printf(TEXT("Object %s is not abstract but AttributeInformation[%d].Name is empty"),
                                        *GetName(),
                                        Index);
                    Context.AddError(FText::FromString(String));
                    Result = EDataValidationResult::Invalid;
                }
                if (AttributeInfo.Description.ToString().IsEmpty())
                {
                    const auto String = FString::Printf(
                        TEXT("Object %s is not abstract but AttributeInformation[%d].Description is empty"),
                        *GetName(),
                        Index);
                    Context.AddError(FText::FromString(String));
                    Result = EDataValidationResult::Invalid;
                }
                Index++;
            }
        }
    }

    return Result;
}
#endif
