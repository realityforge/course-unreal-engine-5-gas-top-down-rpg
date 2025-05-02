#pragma once

#include "ActiveGameplayEffectHandle.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
    ApplyOnBeginOverlap,
    ApplyOnEndOverlap,
    DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
    RemoveOnEndOverlap,
    DoNotRemove
};

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
    void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

    UFUNCTION(BlueprintCallable)
    void OnBeginOverlap(AActor* TargetActor);

    UFUNCTION(BlueprintCallable)
    void OnEndOverlap(AActor* TargetActor);

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = true))
    float ActorEffectLevel{ 1.f };

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Applied Effects",
              meta = (AllowPrivateAccess = true, AllowAbstract = false))
    bool bDestroyOnEffectRemoval{ false };

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Applied Effects",
              meta = (AllowPrivateAccess = true, AllowAbstract = false))
    EEffectApplicationPolicy InstantEffectApplicationPolicy{ EEffectApplicationPolicy::DoNotApply };

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Applied Effects",
              meta = (AllowPrivateAccess = true,
                      AllowAbstract = false,
                      EditCondition = "EEffectApplicationPolicy::DoNotApply != InstantEffectApplicationPolicy",
                      EditConditionHides))
    TSubclassOf<UGameplayEffect> InstantGameplayEffectClass{ nullptr };

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Applied Effects",
              meta = (AllowPrivateAccess = true, AllowAbstract = false))
    EEffectApplicationPolicy DurationEffectApplicationPolicy{ EEffectApplicationPolicy::DoNotApply };

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Applied Effects",
              meta = (AllowPrivateAccess = true,
                      AllowAbstract = false,
                      EditCondition = "EEffectApplicationPolicy::DoNotApply != DurationEffectApplicationPolicy",
                      EditConditionHides))
    TSubclassOf<UGameplayEffect> DurationGameplayEffectClass{ nullptr };

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Applied Effects",
              meta = (AllowPrivateAccess = true, AllowAbstract = false))
    EEffectApplicationPolicy InfiniteEffectApplicationPolicy{ EEffectApplicationPolicy::DoNotApply };

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Applied Effects",
              meta = (AllowPrivateAccess = true,
                      AllowAbstract = false,
                      EditCondition = "EEffectApplicationPolicy::DoNotApply != InfiniteEffectApplicationPolicy",
                      EditConditionHides))
    TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass{ nullptr };

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = "Applied Effects",
              meta = (AllowPrivateAccess = true,
                      AllowAbstract = false,
                      EditCondition = "EEffectApplicationPolicy::DoNotApply != InfiniteEffectApplicationPolicy",
                      EditConditionHides))
    EEffectRemovalPolicy InfiniteEffectRemovalPolicy{ EEffectRemovalPolicy::RemoveOnEndOverlap };

    UPROPERTY()
    TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveGameplayEffectHandles;
};
