#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UCLASS(Abstract)
class AURA_API AAuraEffectActor : public AActor
{
    GENERATED_BODY()

public:
    AAuraEffectActor();

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass) const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowAbstract = false))
    TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass{ nullptr };
};
