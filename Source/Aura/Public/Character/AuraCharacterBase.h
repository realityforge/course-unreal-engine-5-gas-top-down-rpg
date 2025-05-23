#pragma once

#include "CoreMinimal.h"
#include "Interaction/CombatInterface.h"
#include "ModularGasCharacter.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

// TODO: Should refactor AAeonCharacterBase and use that as a base. It may mean refactoring code still in Shokada...

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public AModularGasCharacter, public ICombatInterface
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
    void InitializeDefaultAttributes() const;

    /** Mesh representing the weapon the character is carrying. */
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon{ nullptr };

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet{ nullptr };

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes{ nullptr };

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes{ nullptr };

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultVitalAttributes{ nullptr };

public:
    FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
