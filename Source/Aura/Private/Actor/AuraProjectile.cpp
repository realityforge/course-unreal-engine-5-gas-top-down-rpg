#include "Actor/AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraProjectile)

AAuraProjectile::AAuraProjectile()
{
    // PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;

    Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
    Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
    Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    SetRootComponent(Sphere);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
    ProjectileMovement->InitialSpeed = 550.f;
    ProjectileMovement->MaxSpeed = 550.f;
    ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::BeginPlay()
{
    Super::BeginPlay();

    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void AAuraProjectile::OnSphereOverlap([[maybe_unused]] UPrimitiveComponent* OverlappedComponent,
                                      // ReSharper disable once CppParameterMayBeConstPtrOrRef
                                      [[maybe_unused]] AActor* OtherActor,
                                      [[maybe_unused]] UPrimitiveComponent* OtherComp,
                                      [[maybe_unused]] int32 OtherBodyIndex,
                                      [[maybe_unused]] bool bFromSweep,
                                      [[maybe_unused]] const FHitResult& SweepResult)
{
}
