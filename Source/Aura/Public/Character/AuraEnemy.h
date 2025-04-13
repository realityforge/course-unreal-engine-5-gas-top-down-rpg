#pragma once

#include "Character/AuraCharacterBase.h"
#include "CoreMinimal.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS(Abstract)
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
    GENERATED_BODY()

public:
    virtual void HighlightActor() override;
    virtual void UnHighlightActor() override;
};
