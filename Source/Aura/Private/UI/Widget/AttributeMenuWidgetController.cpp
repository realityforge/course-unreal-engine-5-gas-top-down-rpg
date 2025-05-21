#include "UI/Widget/AttributeMenuWidgetController.h"

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
