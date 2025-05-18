#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

// TODO: Should refactor AAeonCharacterBase and use that as a base. It ma mean refactorin code still in Shokada...

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
    GENERATED_BODY()

public:
    AAuraCharacterBase();

#pragma region IAbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
#pragma endregion

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

private:
    void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level) const;

protected:
    virtual void SetupAbilityActorInfo();

    void InitializeDefaultAttributes() const;

    /** Mesh representing the weapon the character is carrying. */
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon{ nullptr };

    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{ nullptr };

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet{ nullptr };

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes{ nullptr };

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes{ nullptr };

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultVitalAttributes{ nullptr };

public:
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponentFast() const { return AbilitySystemComponent; }
    FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
