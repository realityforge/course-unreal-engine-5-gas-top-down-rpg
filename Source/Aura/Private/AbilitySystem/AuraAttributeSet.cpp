#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
    InitHealth(10.f);
    InitMana(50.f);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldHealth);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldMana);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Strength, OldStrength);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Intelligence, OldIntelligence);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Resilience, OldResilience);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Vigor, OldVigor);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Armor, OldArmor);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ArmorPenetration, OldArmorPenetration);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, BlockChance, OldBlockChance);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CriticalHitChance, OldCriticalHitChance);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CriticalHitDamage, OldCriticalHitDamage);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CriticalHitResistance, OldCriticalHitResistance);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, HealthRegeneration, OldHealthRegeneration);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ManaRegeneration, OldManaRegeneration);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    if (GetHealthAttribute() == Attribute)
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }
    else if (GetManaAttribute() == Attribute)
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
    }
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    FEffectProperties Props;
    GetEffectProperties(Data, Props);

    if (GetHealthAttribute() == Data.EvaluatedData.Attribute)
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }
    else if (GetManaAttribute() == Data.EvaluatedData.Attribute)
    {
        SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
    }
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Intelligence, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Resilience, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Vigor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Armor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ArmorPenetration, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, BlockChance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CriticalHitChance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CriticalHitDamage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, CriticalHitResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, HealthRegeneration, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, ManaRegeneration, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void UAuraAttributeSet::GetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
    // Source = Causer of the effect,
    // Target = Target of the effect (and owner of this AttributeSet)

    Props.EffectContextHandle = Data.EffectSpec.GetContext();
    Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

    if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid()
        && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
        Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
        if (!Props.SourceController && Props.SourceAvatarActor)
        {
            // If the ActorInfo has a null PlayerController then we fall back on trying to
            // access controller from Avatar Actor.
            // Not totally sure ... why ...
            if (const auto Pawn = Cast<APawn>(Props.SourceAvatarActor))
            {
                Props.SourceController = Pawn->GetController();
            }
        }
        if (Props.SourceController)
        {
            Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
        }
    }

    if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
        Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
        Props.TargetASC = &Data.Target;
    }
}
