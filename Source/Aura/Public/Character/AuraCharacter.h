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
    virtual void InitAbilityActorInfo() override;

public:
    AAuraCharacter();

#pragma region ICombatInterface
    virtual int32 GetPlayerLevel() override;
#pragma endregion
};
