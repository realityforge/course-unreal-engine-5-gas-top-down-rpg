#include "UI/Widget/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Misc/DataValidation.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
    check(AttributeInfo);

    // ReSharper disable once CppTooWideScopeInitStatement
    const auto AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

    for (const auto& Entry : AuraAttributeSet->GetAttributeMapRef())
    {
        BroadcastAttributeInfo(Entry.Key, Entry.Value());
    }
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
    check(AttributeInfo);
    // ReSharper disable once CppTooWideScopeInitStatement
    const auto AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

    for (const auto& Entry : AuraAttributeSet->GetAttributeMapRef())
    {
        const auto Tag = Entry.Key;
        const auto Attribute = Entry.Value();
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
            [this, Tag, Attribute](const auto& _) { BroadcastAttributeInfo(Tag, Attribute); });
    }
}

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
