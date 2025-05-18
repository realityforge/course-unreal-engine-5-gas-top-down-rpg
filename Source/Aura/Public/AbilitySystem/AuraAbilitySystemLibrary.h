#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Player/AuraPlayerController.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;

UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintPure,
              Category = "AuraAbilitySystemLibrary",
              meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
    static AAuraPlayerController* GetAuraPlayerController(const UObject* WorldContextObject);
};
