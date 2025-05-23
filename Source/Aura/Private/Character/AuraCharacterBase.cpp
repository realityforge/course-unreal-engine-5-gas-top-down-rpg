#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Misc/DataValidation.h"

static FName NAME_WeaponHandSocket("WeaponHandSocket");

AAuraCharacterBase::AAuraCharacterBase()
{
    PrimaryActorTick.bCanEverTick = false;

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
    }

    return Result;
}
#endif

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

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
    check(IsValid(GetAbilitySystemComponentFast()));

    ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
    ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
    // Initial Vital Attributes are based off Secondary attributes (i.e. Health is based off MaxHealth)
    // Thus we need to apply this effect last
    ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}
