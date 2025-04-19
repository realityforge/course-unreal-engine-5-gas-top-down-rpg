#include "UI/Widget/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
    PlayerController = WidgetControllerParams.PlayerController;
    PlayerState = WidgetControllerParams.PlayerState;
    AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
    AttributeSet = WidgetControllerParams.AttributeSet;
}
