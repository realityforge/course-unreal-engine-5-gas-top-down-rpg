#pragma once

#include "Character/AuraCharacterBase.h"
#include "CoreMinimal.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMotionWarpingComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
    GENERATED_BODY()

    inline static const FName NAME_FacingTarget_WarpTargetName{ "FacingTarget" };

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> CameraComponent{ nullptr };

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USpringArmComponent> SpringArmComponent{ nullptr };

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent{ nullptr };

protected:
    virtual void InitAbilityActorInfo() override;

    UFUNCTION(BlueprintCallable)
    void SetFacingTarget(const FVector& TargetLocation);

    FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }

public:
    explicit AAuraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma region ICombatInterface
    virtual int32 GetPlayerLevel() override;
    virtual void UpdateFacingTarget(const FVector& Target) override;
#pragma endregion
};
