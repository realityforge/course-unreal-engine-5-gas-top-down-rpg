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
    AAuraEnemy();

#pragma region IEnemyInterface
    virtual void HighlightActor() override;
    virtual void UnHighlightActor() override;
#pragma endregion

#pragma region ICombatInterface
    virtual int32 GetPlayerLevel() override;
#pragma endregion

private:
    /** Move this value outside of attributes ... for no reason other than so we can experiment with MMC  */
    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Character Class Defaults",
              meta = (AllowPrivateAccess = true))
    int32 Level{ 1 };
};
