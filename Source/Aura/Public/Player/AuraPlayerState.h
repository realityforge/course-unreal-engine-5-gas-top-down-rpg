#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AAuraPlayerState();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{ nullptr };

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet{ nullptr };

private:
    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
    int32 Level{ 1 };

    UFUNCTION()
    void OnRep_Level(int32 OldLevel);

public:
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponentFast() const { return AbilitySystemComponent; }
    FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
    FORCEINLINE int32 GetPlayerLevel() const { return Level; }
};
