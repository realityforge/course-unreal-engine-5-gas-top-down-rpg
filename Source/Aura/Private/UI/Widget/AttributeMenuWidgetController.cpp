#include "UI/Widget/AttributeMenuWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues() {}

void UAttributeMenuWidgetController::BindCallbacksToDependencies() {}

#if WITH_EDITOR
EDataValidationResult UAttributeMenuWidgetController::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        if (!IsValid(AttributeInfo))
        {
            const auto String = FString::Printf(TEXT("Object %s is not an abstract class and "
                                                     "has not specified the property AttributeInfo"),
                                                *GetName());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }

    return Result;
}
#endif

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                            const FGameplayAttribute& Attribute) const
{
    // ReSharper disable once CppTooWideScopeInitStatement
    const auto AttributeDef = AttributeInfo->FindAttributeDefForTag(AttributeTag);
    if (AttributeDef.IsValid())
    {
        const float Value = Attribute.GetNumericValue(AttributeSet);
        AttributeInfoDelegate.Broadcast(FAuraAttributeInfo{ AttributeDef, Value });
    }
}
