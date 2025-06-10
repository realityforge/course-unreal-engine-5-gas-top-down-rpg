#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameplayEffectTypes.h"
#include "Misc/DataValidation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraCharacterBase)

static FName NAME_WeaponHandSocket("WeaponHandSocket");

AAuraCharacterBase::AAuraCharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = false;

    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
    GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
    Weapon->SetupAttachment(GetMesh(), NAME_WeaponHandSocket);
    Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#if WITH_EDITOR
EDataValidationResult AAuraCharacterBase::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        // ReSharper disable once CppTooWideScopeInitStatement
        const auto SkeletalMeshAsset = GetMesh()->GetSkeletalMeshAsset();
        if (!IsValid(SkeletalMeshAsset))
        {
            const auto String = FString::Printf(TEXT("Object %s is not an abstract class but has not specified "
                                                     "the property Mesh.SkeletalMeshAsset"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        else if (nullptr == GetMesh()->GetSocketByName(NAME_WeaponHandSocket))
        {
            const auto String = FString::Printf(TEXT("Object %s has Mesh component that references StaticMeshAsset %s "
                                                     "but the asset does not have a socket named %s as expected"),
                                                *GetActorNameOrLabel(),
                                                *SkeletalMeshAsset->GetName(),
                                                *NAME_WeaponHandSocket.ToString());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        if (!WeaponTipSocketName.IsValid())
        {
            const auto String = FString::Printf(TEXT("Object %s is not an abstract class but has not specified "
                                                     "the property WeaponTipSocketName"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }

        // ReSharper disable once CppTooWideScopeInitStatement
        const auto WeaponSkeletalMeshAsset = Weapon->GetSkeletalMeshAsset();
        if (!IsValid(WeaponSkeletalMeshAsset))
        {
            const auto String = FString::Printf(TEXT("Object %s is not an abstract class but has not specified "
                                                     "the property Weapon.SkeletalMeshAsset"),
                                                *GetActorNameOrLabel());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
        else if (WeaponTipSocketName.IsValid() && nullptr == Weapon->GetSocketByName(WeaponTipSocketName))
        {
            const auto String =
                FString::Printf(TEXT("Object %s has Weapon component that references StaticMeshAsset %s "
                                     "but the asset does not have a socket named '%s' as expected"),
                                *GetActorNameOrLabel(),
                                *WeaponSkeletalMeshAsset->GetName(),
                                *WeaponTipSocketName.ToString());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }

    return Result;
}
#endif

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
    check(Weapon);
    return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass,
                                           const float Level) const
{
    const auto ASC = GetAbilitySystemComponentFast();
    check(IsValid(ASC));

    if (IsValid(GameplayEffectClass))
    {
        auto ContextHandle = ASC->MakeEffectContext();
        // Configure SourceObject (We use it in MMC_MaxHealth and MMC_MaxMana)
        ContextHandle.AddSourceObject(this);
        const auto SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
        ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
    }
}

void AAuraCharacterBase::OnAbilitySystemComponentInitialized()
{
    if (const auto AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponentFast()))
    {
        AuraAbilitySystemComponent->AbilityActorInfoSet();
    }
}
