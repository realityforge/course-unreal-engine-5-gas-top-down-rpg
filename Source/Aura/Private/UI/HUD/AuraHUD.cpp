#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "Misc/DataValidation.h"
#include "Player/AuraPlayerController.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/OverlayWidgetController.h"

UAuraUserWidget* AAuraHUD::CreateOverlayWidget()
{
    checkf(OverlayWidgetClass, TEXT("AAuraHUD has not specified the property OverlayWidgetClass"));
    checkf(OverlayWidgetControllerClass, TEXT("AAuraHUD has not specified the property OverlayWidgetControllerClass"));
    const auto PlayerController = CastChecked<AAuraPlayerController>(PlayerOwner);

    const auto WidgetControllerParams = PlayerController->CreateWidgetControllerParams();
    OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
    OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);

    OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget->SetWidgetController(OverlayWidgetController);
    return OverlayWidget;
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
