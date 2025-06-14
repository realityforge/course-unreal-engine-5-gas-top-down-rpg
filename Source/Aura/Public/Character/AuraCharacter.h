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

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> CameraComponent{ nullptr };

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USpringArmComponent> SpringArmComponent{ nullptr };

protected:
    virtual void InitAbilityActorInfo() override;

public:
    explicit AAuraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma region ICombatInterface
    virtual int32 GetPlayerLevel() override;
#pragma endregion
};
