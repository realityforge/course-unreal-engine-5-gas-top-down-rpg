#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UAuraAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<APlayerController> PlayerController{ nullptr };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<APlayerState> PlayerState{ nullptr };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{ nullptr };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAttributeSet> AttributeSet{ nullptr };

    FWidgetControllerParams() {}
    FWidgetControllerParams(APlayerController* InPlayerController,
                            APlayerState* InPlayerState,
                            UAbilitySystemComponent* InAbilitySystemComponent,
                            UAttributeSet* InAttributeSet)
        : PlayerController(InPlayerController)
        , PlayerState(InPlayerState)
        , AbilitySystemComponent(InAbilitySystemComponent)
        , AttributeSet(InAttributeSet)
    {
    }
};

UCLASS(Abstract)
class AURA_API UAuraWidgetController : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams);

    /**
     * Method that emits any events from controller to setup initial values exposed to any views.
     */
    virtual void BroadcastInitialValues();

    /**
     * Method responsible for adding delegates to receive changes that the controller attempts to monitor.
     * For example, this is where we bind delegates to monitor attribute changes or effect characteristics.
     */
    virtual void BindCallbacksToDependencies();

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
