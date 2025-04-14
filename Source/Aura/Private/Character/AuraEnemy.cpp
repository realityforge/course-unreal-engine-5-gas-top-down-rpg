#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
    // Block visibility. Used so that the under cursor trace (for highlighting) will
    // intersect with enemy mesh.
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
    GetMesh()->SetRenderCustomDepth(true);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    if (Weapon)
    {
        Weapon->SetRenderCustomDepth(true);
        Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
    }
}

void AAuraEnemy::UnHighlightActor()
{
    if (Weapon)
    {
        Weapon->SetRenderCustomDepth(false);
        Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_CLEAR);
    }
    GetMesh()->SetRenderCustomDepth(false);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_CLEAR);
}
