#include "Actor/AuraEffectActor.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    SetRootComponent(Mesh);

    CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
    CollisionSphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                      AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp,
                                      int32 OtherBodyIndex,
                                      bool bFromSweep,
                                      const FHitResult& SweepResult)
{
    // TODO: Change this to use GameplayEffect in the future rather than using ugly const_cast
    if (const auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
    {
        const auto AuraAttributeSet =
            CastChecked<UAuraAttributeSet>(ASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
        const auto MutableAuraAttributes = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
        MutableAuraAttributes->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
        Destroy();
    }
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                    AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp,
                                    int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay()
{
    Super::BeginPlay();
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
    CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}
