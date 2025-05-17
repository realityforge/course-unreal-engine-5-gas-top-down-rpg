#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
    auto& Manager = UGameplayTagsManager::Get();

    GameplayTags.Attributes_Primary_Strength =
        Manager.AddNativeGameplayTag(FName("Attributes.Primary.Strength"), TEXT("Increases physical damage"));
    GameplayTags.Attributes_Primary_Intelligence =
        Manager.AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), TEXT("Increases magical damage"));
    GameplayTags.Attributes_Primary_Resilience =
        Manager.AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),
                                     TEXT("Increases Armor and Armor Penetration"));
    GameplayTags.Attributes_Primary_Vigor =
        Manager.AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), TEXT("Increases Health"));

    GameplayTags.Attributes_Secondary_Armor =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),
                                     TEXT("Reduces damage taken, improves Block Chance"));
    GameplayTags.Attributes_Secondary_ArmorPenetration =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),
                                     TEXT("Ignores Percentage of enemy Armor, increases Critical Hit Chance"));
    GameplayTags.Attributes_Secondary_BlockChance =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),
                                     TEXT("Chance to cut incoming damage in half"));
    GameplayTags.Attributes_Secondary_CriticalHitChance =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),
                                     TEXT("Chance to double damage plus critical hit bonus"));
    GameplayTags.Attributes_Secondary_CriticalHitDamage =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),
                                     TEXT("Bonus damage added when a critical hit is scored"));
    GameplayTags.Attributes_Secondary_CriticalHitResistance =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),
                                     TEXT("Reduces Critical Hit Chance of attacking enemies"));
    GameplayTags.Attributes_Secondary_HealthRegeneration =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),
                                     TEXT("Amount of Health regenerated every 1 second"));
    GameplayTags.Attributes_Secondary_ManaRegeneration =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),
                                     TEXT("Amount of Mana regenerated every 1 second"));
    GameplayTags.Attributes_Secondary_MaxHealth =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),
                                     TEXT("Maximum amount of Health obtainable"));
    GameplayTags.Attributes_Secondary_MaxMana =
        Manager.AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), TEXT("Maximum amount of Mana obtainable"));
}
