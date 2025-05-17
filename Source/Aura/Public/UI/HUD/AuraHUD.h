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
    UPROPERTY()
    TObjectPtr<UAuraUserWidget> OverlayWidget;

    UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);

    void InitOverlay(APlayerController* PlayerController,
                     APlayerState* PlayerState,
                     UAbilitySystemComponent* AbilitySystemComponent,
                     UAttributeSet* AttributeSet);

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

private:
    UPROPERTY(EditAnywhere)
    TSubclassOf<UAuraUserWidget> OverlayWidgetClass{ nullptr };

    UPROPERTY(EditAnywhere)
    TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass{ nullptr };

    UPROPERTY()
    TObjectPtr<UOverlayWidgetController> OverlayWidgetController{ nullptr };
};
