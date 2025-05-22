#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
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
    UAuraUserWidget* CreateOverlayWidget();

    UFUNCTION(BlueprintCallable)
    UAuraUserWidget* CreateAttributeMenuWidget();

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

#pragma region AttributeMenuWidget

    UPROPERTY(EditAnywhere)
    TSubclassOf<UAuraUserWidget> AttributeMenuWidgetClass{ nullptr };

    UPROPERTY(EditAnywhere)
    TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass{ nullptr };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TObjectPtr<UAuraUserWidget> AttributeMenuWidget{ nullptr };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController{ nullptr };

#pragma endregion
};
