#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "Misc/DataValidation.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
    if (IsValid(OverlayWidgetController))
    {
        return OverlayWidgetController;
    }
    else
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
        return OverlayWidgetController;
    }
}

void AAuraHUD::CreateOverlayWidgetOverlay(const FWidgetControllerParams& WidgetControllerParams)
{
    checkf(OverlayWidgetClass, TEXT("AAuraHUD has not specified the property OverlayWidgetClass"));
    checkf(OverlayWidgetControllerClass, TEXT("AAuraHUD has not specified the property OverlayWidgetControllerClass"));
    OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);

    OverlayWidget->SetWidgetController(GetOverlayWidgetController(WidgetControllerParams));
    OverlayWidget->AddToViewport();
}

EDataValidationResult AAuraHUD::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        if (!IsValid(OverlayWidgetClass))
        {
            const auto String = FString::Printf(TEXT("Object %s is not abstract but has not specified "
                                                     "the property OverlayWidgetClass"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        if (!IsValid(OverlayWidgetControllerClass))
        {
            const auto String = FString::Printf(TEXT("Object %s is not abstract but has not specified "
                                                     "the property OverlayWidgetControllerClass"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }

    return Result;
}
