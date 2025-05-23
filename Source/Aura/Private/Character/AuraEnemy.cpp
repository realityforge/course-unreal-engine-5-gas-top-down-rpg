#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
    // Block visibility. Used so that the under cursor trace (for highlighting) will
    // intersect with enemy mesh.
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    SetOwnerPolicy(EAbilitySystemComponentOwnerPolicy::CharacterOwned);
    SetSetupPolicy(EAbilitySystemComponentSetupPolicy::BeginPlay);

    const auto ASC = CreateDefaultSubobject<UAuraAbilitySystemComponent>(NAME_AbilitySystemComponent);
    ASC->SetIsReplicated(true);
    ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
    SetAbilitySystemComponent(ASC);

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

void AAuraEnemy::InitAbilityActorInfo()
{
    Super::InitAbilityActorInfo();

    InitializeDefaultAttributes();
    if (const auto AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponentFast()))
    {
        AuraAbilitySystemComponent->AbilityActorInfoSet();
    }
}
