#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS(Abstract)
class AURA_API AAuraPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AAuraPlayerController();

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> InputMappingContext{ nullptr };
};
