#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraEnemy)

AAuraEnemy::AAuraEnemy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UAuraAbilitySystemComponent>(NAME_AbilitySystemComponent))
{
    // Block visibility. Used so that the under cursor trace (for highlighting) will
    // intersect with enemy mesh.
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    SetOwnerPolicy(EAbilitySystemComponentOwnerPolicy::CharacterOwned);
    SetSetupPolicy(EAbilitySystemComponentSetupPolicy::BeginPlay);

    GetAbilitySystemComponentFast()->SetIsReplicated(true);
    GetAbilitySystemComponentFast()->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{
    GetMesh()->SetRenderCustomDepth(true);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    Weapon->SetRenderCustomDepth(true);
    Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
    Weapon->SetRenderCustomDepth(false);
    Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_CLEAR);
    GetMesh()->SetRenderCustomDepth(false);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_CLEAR);
}

int32 AAuraEnemy::GetPlayerLevel()
{
    return Level;
}
