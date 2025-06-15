#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class AURA_API AAuraProjectile : public AActor
{
    GENERATED_BODY()

public:
    AAuraProjectile();

    virtual void Destroyed() override;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
                         AActor* OtherActor,
                         UPrimitiveComponent* OtherComp,
                         int32 OtherBodyIndex,
                         bool bFromSweep,
                         const FHitResult& SweepResult);

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UProjectileMovementComponent> ProjectileMovement{ nullptr };

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USphereComponent> Sphere{ nullptr };

    UPROPERTY(EditDefaultsOnly, meta = (RuleRangerRequired))
    TObjectPtr<UNiagaraSystem> ImpactEffect{ nullptr };

    UPROPERTY(EditDefaultsOnly, meta = (RuleRangerRequired))
    TObjectPtr<USoundBase> ImpactSound{ nullptr };

    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
    TObjectPtr<UAudioComponent> LoopingAudio{ nullptr };

    UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
    TObjectPtr<USoundBase> LoopingSound{ nullptr };

    /** flag indicating whether the overlap effects have been played or not */
    bool bHit{ false };

    void PlayImpactCosmetics() const;
};
