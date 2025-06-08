#pragma once

#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "CoreMinimal.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;

UCLASS(Abstract)
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility
{
    GENERATED_BODY()

public:
#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TSubclassOf<AAuraProjectile> ProjectileClass{ nullptr };

    UFUNCTION(BlueprintCallable, Category = "Projectile")
    void SpawnProjectile() const;
};
