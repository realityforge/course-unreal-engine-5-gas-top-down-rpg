#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "UI/Widget/AuraWidgetController.h"
#include "AuraPlayerController.generated.h"

class UAeonAbilitySystemComponent;
class UAeonInputConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS(Abstract)
class AURA_API AAuraPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AAuraPlayerController();

    virtual void PlayerTick(float DeltaTime) override;

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

    FWidgetControllerParams CreateWidgetControllerParams();

protected:
    virtual void SetupInputComponent() override;

    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAeonInputConfig> InputConfig{ nullptr };

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> MoveAction{ nullptr };

    UPROPERTY()
    TObjectPtr<UAeonAbilitySystemComponent> AeonAbilitySystemComponent{ nullptr };

    void Move(const FInputActionValue& InputActionValue);

    TScriptInterface<IEnemyInterface> LastActorUnderCursor{ nullptr };
    TScriptInterface<IEnemyInterface> CurrentActorUnderCursor{ nullptr };

    void CursorTrace();

    UAeonAbilitySystemComponent* GetAeonAbilitySystemComponent();

    void Input_AbilityInputPressed(const FGameplayTag InGameplayTag);
    void Input_AbilityInputReleased(const FGameplayTag InGameplayTag);
    void Input_AbilityInputHeld(const FGameplayTag InGameplayTag);
};
