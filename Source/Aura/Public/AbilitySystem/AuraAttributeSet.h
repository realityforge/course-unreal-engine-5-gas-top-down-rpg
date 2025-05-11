#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)           \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
    GENERATED_BODY()

    FEffectProperties() {}

    FGameplayEffectContextHandle EffectContextHandle;

    UPROPERTY()
    UAbilitySystemComponent* SourceASC{ nullptr };

    UPROPERTY()
    AActor* SourceAvatarActor{ nullptr };

    UPROPERTY()
    AController* SourceController{ nullptr };

    UPROPERTY()
    ACharacter* SourceCharacter{ nullptr };

    UPROPERTY()
    UAbilitySystemComponent* TargetASC{ nullptr };

    UPROPERTY()
    AActor* TargetAvatarActor{ nullptr };

    UPROPERTY()
    AController* TargetController{ nullptr };

    UPROPERTY()
    ACharacter* TargetCharacter{ nullptr };
};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UAuraAttributeSet();

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(ThisClass, Health);

    UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Mana)
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(ThisClass, Mana);

    /** Attribute that increases Physical Damage. */
    UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Strength)
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(ThisClass, Strength);

    /** Attribute that increases Magical Damage. */
    UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Intelligence)
    FGameplayAttributeData Intelligence;
    ATTRIBUTE_ACCESSORS(ThisClass, Intelligence);

    /** Attribute that increases Armor and Armor Penetration. */
    UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Resilience)
    FGameplayAttributeData Resilience;
    ATTRIBUTE_ACCESSORS(ThisClass, Resilience);

    /** Attribute that increases Health. */
    UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes", ReplicatedUsing = OnRep_Vigor)
    FGameplayAttributeData Vigor;
    ATTRIBUTE_ACCESSORS(ThisClass, Vigor);

    /**
     * Attribute that reduces damage taken and improves block chance.
     * Depends on Resilience.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_Armor)
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(ThisClass, Armor);

    /**
     * Attribute that ignores a percentage of enemy Armor and increases Critical Hit chance.
     * Depends on Resilience.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_ArmorPenetration)
    FGameplayAttributeData ArmorPenetration;
    ATTRIBUTE_ACCESSORS(ThisClass, ArmorPenetration);

    /**
     * Attribute that indicates the chance to "block" and cut incoming damage in half.
     * Depends on Armor.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_BlockChance)
    FGameplayAttributeData BlockChance;
    ATTRIBUTE_ACCESSORS(ThisClass, BlockChance);

    /**
     * Attribute that indicates the chance to "critical hit" and double damagae plus add a critical hit bonus.
     * Depends on Armor Penetration.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitChance)
    FGameplayAttributeData CriticalHitChance;
    ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitChance);

    /**
     * Attribute that indicates the damage added when a critical hit is scored.
     * Depends on Armor Penetration.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitDamage)
    FGameplayAttributeData CriticalHitDamage;
    ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitDamage);

    /**
     * Attribute that reduces the critical hit chance of attacking enemies.
     * Depends on Armor.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_CriticalHitResistance)
    FGameplayAttributeData CriticalHitResistance;
    ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitResistance);

    /**
     * Attribute that indicates the amount of health regenerated every 1 second.
     * Depends on Vigor.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_HealthRegeneration)
    FGameplayAttributeData HealthRegeneration;
    ATTRIBUTE_ACCESSORS(ThisClass, HealthRegeneration);

    /**
     * Attribute that indicates the amount of mana regenerated every 1 second.
     * Depends on Intelligence.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_ManaRegeneration)
    FGameplayAttributeData ManaRegeneration;
    ATTRIBUTE_ACCESSORS(ThisClass, ManaRegeneration);

    /**
     * Attribute that indicates the maximum amount of Health obtainable.
     * Depends on Vigor.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);

    /**
     * Attribute that indicates the maximum amount of Mana obtainable.
     * Depends on MaxMana.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes", ReplicatedUsing = OnRep_MaxMana)
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);

    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth);

    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldMana);

    UFUNCTION()
    void OnRep_Strength(const FGameplayAttributeData& OldStrength);

    UFUNCTION()
    void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

    UFUNCTION()
    void OnRep_Resilience(const FGameplayAttributeData& OldResilience);

    UFUNCTION()
    void OnRep_Vigor(const FGameplayAttributeData& OldVigor);

    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldArmor);

    UFUNCTION()
    void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);

    UFUNCTION()
    void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);

    UFUNCTION()
    void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance);

    UFUNCTION()
    void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage);

    UFUNCTION()
    void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance);

    UFUNCTION()
    void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration);

    UFUNCTION()
    void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration);

    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

    UFUNCTION()
    void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    // No idea why we do this at all here in attributes ...
    void GetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
