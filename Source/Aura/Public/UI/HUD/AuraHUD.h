#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;

UCLASS(Abstract)
class AURA_API AAuraHUD : public AHUD
{
    GENERATED_BODY()

public:
    UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);

    void CreateOverlayWidgetOverlay(const FWidgetControllerParams& WidgetControllerParams);

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

private:
#pragma region OverlayWidget

    UPROPERTY(EditAnywhere)
    TSubclassOf<UAuraUserWidget> OverlayWidgetClass{ nullptr };

    UPROPERTY(EditAnywhere)
    TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass{ nullptr };

    UPROPERTY()
    TObjectPtr<UAuraUserWidget> OverlayWidget{ nullptr };

    UPROPERTY()
    TObjectPtr<UOverlayWidgetController> OverlayWidgetController{ nullptr };

#pragma endregion
};
