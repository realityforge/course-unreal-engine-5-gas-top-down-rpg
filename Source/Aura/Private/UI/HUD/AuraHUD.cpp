#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "Misc/DataValidation.h"
#include "Player/AuraPlayerController.h"
#include "UI/Widget/AttributeMenuWidgetController.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/OverlayWidgetController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraHUD)

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

UAuraUserWidget* AAuraHUD::CreateAttributeMenuWidget()
{
    checkf(AttributeMenuWidgetClass, TEXT("AAuraHUD has not specified the property AttributeMenuWidgetClass"));
    checkf(AttributeMenuWidgetControllerClass,
           TEXT("AAuraHUD has not specified the property AttributeMenuWidgetControllerClass"));

    const auto PlayerController = CastChecked<AAuraPlayerController>(PlayerOwner);

    // The alternative to making the HUD the factory is to make the widget instantiate controller in Construct event

    const auto WidgetControllerParams = PlayerController->CreateWidgetControllerParams();

    AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
    AttributeMenuWidgetController->SetWidgetControllerParams(WidgetControllerParams);

    AttributeMenuWidget = NewObject<UAuraUserWidget>(this, AttributeMenuWidgetClass);
    AttributeMenuWidget->SetWidgetController(AttributeMenuWidgetController);
    return AttributeMenuWidget;
}

#if WITH_EDITOR
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
        if (!IsValid(AttributeMenuWidgetClass))
        {
            const auto String = FString::Printf(TEXT("Object %s is not abstract but has not specified "
                                                     "the property AttributeMenuWidgetClass"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        if (!IsValid(AttributeMenuWidgetControllerClass))
        {
            const auto String = FString::Printf(TEXT("Object %s is not abstract but has not specified "
                                                     "the property AttributeMenuWidgetControllerClass"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }

    return Result;
}
#endif
