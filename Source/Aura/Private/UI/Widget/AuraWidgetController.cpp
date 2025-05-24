#include "UI/Widget/AuraWidgetController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraWidgetController)

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
    PlayerController = WidgetControllerParams.PlayerController;
    PlayerState = WidgetControllerParams.PlayerState;
    AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
    AttributeSet = WidgetControllerParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues() {}

void UAuraWidgetController::BindCallbacksToDependencies() {}
