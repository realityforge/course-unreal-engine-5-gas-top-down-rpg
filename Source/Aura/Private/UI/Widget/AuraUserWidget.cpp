#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
    WidgetController = InWidgetController;
    WidgetControllerSet();
    // TODO: Why not invoke the following here?
    //       WidgetController->BroadcastInitialValues();
    //       WidgetController->BindCallbacksToDependencies();
}
