﻿#include "AuraGameplayTags.h"

namespace AuraGameplayTags
{
    // --------------------------------------------------- //
    // Primary Attribute Tags
    // --------------------------------------------------- //

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Primary_Strength,
                                   "Attributes.Primary.Strength",
                                   "Increases physical damage")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Primary_Intelligence,
                                   "Attributes.Primary.Intelligence",
                                   "Increases magical damage")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Primary_Resilience,
                                   "Attributes.Primary.Resilience",
                                   "Increases Armor and Armor Penetration")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Primary_Vigor, "Attributes.Primary.Vigor", "Increases Health")

    // --------------------------------------------------- //
    // Secondary Attribute Tags
    // --------------------------------------------------- //

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_Armor,
                                   "Attributes.Secondary.Armor",
                                   "Reduces damage taken, improves Block Chance")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_ArmorPenetration,
                                   "Attributes.Secondary.ArmorPenetration",
                                   "Ignores Percentage of enemy Armor, increases Critical Hit Chance")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_BlockChance,
                                   "Attributes.Secondary.BlockChance",
                                   "Chance to cut incoming damage in half")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_CriticalHitChance,
                                   "Attributes.Secondary.CriticalHitChance",
                                   "Chance to double damage plus critical hit bonus")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_CriticalHitDamage,
                                   "Attributes.Secondary.CriticalHitDamage",
                                   "Bonus damage added when a critical hit is scored")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_CriticalHitResistance,
                                   "Attributes.Secondary.CriticalHitResistance",
                                   "Reduces Critical Hit Chance of attacking enemies")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_HealthRegeneration,
                                   "Attributes.Secondary.HealthRegeneration",
                                   "Amount of Health regenerated every 1 second")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_ManaRegeneration,
                                   "Attributes.Secondary.ManaRegeneration",
                                   "Amount of Mana regenerated every 1 second")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_MaxHealth,
                                   "Attributes.Secondary.MaxHealth",
                                   "Maximum amount of Health obtainable")
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attributes_Secondary_MaxMana,
                                   "Attributes.Secondary.MaxMana",
                                   "Maximum amount of Mana obtainable")
} // namespace AuraGameplayTags
