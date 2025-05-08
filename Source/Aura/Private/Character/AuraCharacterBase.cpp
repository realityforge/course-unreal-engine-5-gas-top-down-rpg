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

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
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

void AAuraCharacterBase::BeginPlay()
{
    Super::BeginPlay();
}

void AAuraCharacterBase::SetupAbilityActorInfo() {}

void AAuraCharacterBase::InitializePrimaryAttributes() const
{
    check(IsValid(AbilitySystemComponent));
    if (IsValid(DefaultPrimaryAttributes))
    {
        const auto ContextHandle = AbilitySystemComponent->MakeEffectContext();
        const auto SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, ContextHandle);
        AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
    }
}
