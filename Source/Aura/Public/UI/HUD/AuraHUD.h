#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;

UCLASS(Abstract)
class AURA_API AAuraHUD : public AHUD
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TObjectPtr<UUserWidget> OverlayWidget;

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> OverlayWidgetClass;
};
