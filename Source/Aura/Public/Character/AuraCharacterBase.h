#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
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

protected:
    virtual void BeginPlay() override;

    virtual void SetupAbilityActorInfo();

    void InitializePrimaryAttributes() const;

    /** Mesh representing the weapon the character is carrying. */
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon{ nullptr };

    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{ nullptr };

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet{ nullptr };

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes{ nullptr };

public:
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponentFast() const { return AbilitySystemComponent; }
    FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
