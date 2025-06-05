#pragma once

#include "CoreMinimal.h"
#include "ModularGasPlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraPlayerState : public AModularGasPlayerState
{
    GENERATED_BODY()

public:
    explicit AAuraPlayerState(const FObjectInitializer& ObjectInitializer);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet{ nullptr };

private:
    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
    int32 Level{ 1 };

    UFUNCTION()
    void OnRep_Level(int32 OldLevel);

public:
    FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
    FORCEINLINE int32 GetPlayerLevel() const { return Level; }
};
