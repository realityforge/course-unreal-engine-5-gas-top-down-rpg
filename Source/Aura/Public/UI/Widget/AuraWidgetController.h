#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UAuraAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API UAuraWidgetController : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
    TObjectPtr<APlayerController> PlayerController{ nullptr };
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
    TObjectPtr<APlayerState> PlayerState{ nullptr };
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{ nullptr };
    UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
    TObjectPtr<UAttributeSet> AttributeSet{ nullptr };
};
