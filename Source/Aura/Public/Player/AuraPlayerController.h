#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "UI/Widget/AuraWidgetController.h"
#include "AuraPlayerController.generated.h"

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
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> InputMappingContext{ nullptr };

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> MoveAction{ nullptr };

    void Move(const FInputActionValue& InputActionValue);

    TScriptInterface<IEnemyInterface> LastActorUnderCursor{ nullptr };
    TScriptInterface<IEnemyInterface> CurrentActorUnderCursor{ nullptr };

    void CursorTrace();
};
