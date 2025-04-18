#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "Misc/DataValidation.h"

EDataValidationResult AAuraHUD::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        if (!IsValid(OverlayWidgetClass))
        {
            const auto String =
                FString::Printf(TEXT("Object %s is not abstract but has not specified the property OverlayWidgetClass"),
                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }

    return Result;
}

void AAuraHUD::BeginPlay()
{
    Super::BeginPlay();
    OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget->AddToViewport();
}
