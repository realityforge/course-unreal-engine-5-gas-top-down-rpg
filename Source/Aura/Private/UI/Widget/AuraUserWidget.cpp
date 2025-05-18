#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/AuraWidgetController.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
    WidgetController = InWidgetController;
    WidgetControllerSet();
    if (const auto AuraWidgetController = Cast<UAuraWidgetController>(WidgetController))
    {
        AuraWidgetController->BroadcastInitialValues();
        AuraWidgetController->BindCallbacksToDependencies();
    }
}
