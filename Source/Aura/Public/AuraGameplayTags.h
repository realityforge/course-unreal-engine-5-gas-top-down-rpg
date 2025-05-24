#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace AuraGameplayTags
{
    // --------------------------------------------------- //
    // Primary Attribute Tags
    // --------------------------------------------------- //

    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Strength)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Intelligence)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Resilience)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Vigor)

    // --------------------------------------------------- //
    // Secondary Attribute Tags
    // --------------------------------------------------- //

    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Armor)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ArmorPenetration)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_BlockChance)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitChance)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitDamage)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitResistance)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_HealthRegeneration)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ManaRegeneration)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHealth)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxMana)

    // --------------------------------------------------- //
    // Message Tags
    // --------------------------------------------------- //

    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_HealthCrystal)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_HealthPotion)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_ManaCrystal)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_ManaPotion)

    // --------------------------------------------------- //
    // Input Tags
    // --------------------------------------------------- //

    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Mouse_LeftButton)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Mouse_RightButton)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Keyboard_1)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Keyboard_2)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Keyboard_3)
    AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Keyboard_4)

} // namespace AuraGameplayTags
