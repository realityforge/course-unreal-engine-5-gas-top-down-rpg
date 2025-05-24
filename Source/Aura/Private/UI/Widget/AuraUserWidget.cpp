#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/AuraWidgetController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraUserWidget)

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
