#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "AuraUserWidget.generated.h"

UCLASS(Abstract)
class AURA_API UAuraUserWidget : public UUserWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TObjectPtr<UObject> WidgetController;

protected:
    /** Invoked after the WidgetController has been set. */
    UFUNCTION(BlueprintImplementableEvent)
    void WidgetControllerSet();

    UFUNCTION(BlueprintCallable)
    void SetWidgetController(UObject* InWidgetController);
};
