#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
    GENERATED_BODY()

public:
    AAuraEffectActor();

    UFUNCTION()
    virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                AActor* OtherActor,
                                UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex,
                                bool bFromSweep,
                                const FHitResult& SweepResult);
    UFUNCTION()
    virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
                              AActor* OtherActor,
                              UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> Mesh{ nullptr };

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USphereComponent> CollisionSphere{ nullptr };
};
