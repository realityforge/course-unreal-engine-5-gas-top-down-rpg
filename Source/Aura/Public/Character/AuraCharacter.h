#pragma once

#include "Character/AuraCharacterBase.h"
#include "CoreMinimal.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TObjectPtr<UCameraComponent> CameraComponent{ nullptr };

    UPROPERTY(EditAnywhere)
    TObjectPtr<USpringArmComponent> SpringArmComponent{ nullptr };

protected:
    virtual void SetupAbilityActorInfo() override;

public:
    AAuraCharacter();

    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;

#pragma region ICombatInterface
    virtual int32 GetPlayerLevel() override;
#pragma endregion
};
