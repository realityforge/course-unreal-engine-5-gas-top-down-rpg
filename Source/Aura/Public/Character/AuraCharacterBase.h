#pragma once

#include "Aeon/Character/AeonCharacterBase.h"
#include "CoreMinimal.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public AAeonCharacterBase, public ICombatInterface
{
    GENERATED_BODY()

public:
    AAuraCharacterBase();

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

private:
    void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level) const;

protected:
    virtual void OnAbilitySystemComponentInitialized() override;

    /** Mesh representing the weapon the character is carrying. */
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon{ nullptr };

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet{ nullptr };

public:
    FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
