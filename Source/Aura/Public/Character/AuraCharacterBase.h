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
    explicit AAuraCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

#pragma region ICombatInterface
    virtual FVector GetCombatSocketLocation() override;
#pragma endregion

private:
    /** The socket name on the weapon mesh from which projectiles are emitted. */
    UPROPERTY(EditAnywhere, Category = "Combat")
    FName WeaponTipSocketName{ NAME_None };

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
