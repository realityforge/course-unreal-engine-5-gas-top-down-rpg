#include "Actor/AuraProjectile.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

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

void AAuraProjectile::PlayImpactCosmetics() const
{
    UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation(), FRotator::ZeroRotator);
    if (LoopingSound)
    {
        LoopingAudio->Stop();
    }
}

void AAuraProjectile::Destroyed()
{
    if (!bHit && !HasAuthority())
    {
        // If we have not had the overlap occur on the client and thus
        // have not played the cosmetic effects then do so now. If
        // bHit is true then we assume that they are already completed
        //
        // NOTE: Seems silly to do it here only on the client (why not push it
        // always here as overlap == destroy?). Actually why not GameplayCue or
        // something more sophisticated?
        PlayImpactCosmetics();
    }
    Super::Destroyed();
}

void AAuraProjectile::BeginPlay()
{
    Super::BeginPlay();

    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);

    if (LoopingSound)
    {
        LoopingAudio = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
    }
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
    // The projectile will often start overlapping with the character that fired it so
    // let's just ignore that for now.
    //
    // TODO: When we can get the projectile correctly emitted from socket on the staff
    //       on both server and client then we should revise this guard.
    if (GetOwner() != OtherActor)
    {
        PlayImpactCosmetics();
        if (HasAuthority())
        {
            Destroy();
        }
        else
        {
            bHit = true;
        }
    }
}
