#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Misc/DataValidation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraEffectActor)

AAuraEffectActor::AAuraEffectActor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

#if WITH_EDITOR
EDataValidationResult AAuraEffectActor::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        if (!IsValid(InstantGameplayEffectClass)
            && EEffectApplicationPolicy::DoNotApply != InstantEffectApplicationPolicy)
        {
            const auto String =
                FString::Printf(TEXT("Object %s is not an abstract class and has specified an "
                                     "InstantEffectApplicationPolicy of %s but has not specified "
                                     "the property InstantGameplayEffectClass."),
                                *GetActorNameOrLabel(),
                                *StaticEnum<EEffectApplicationPolicy>()
                                     ->GetDisplayNameTextByValue(static_cast<int32>(InstantEffectApplicationPolicy))
                                     .ToString());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }

        if (!IsValid(DurationGameplayEffectClass)
            && EEffectApplicationPolicy::DoNotApply != DurationEffectApplicationPolicy)
        {
            const auto String =
                FString::Printf(TEXT("Object %s is not an abstract class and has specified an "
                                     "DurationEffectApplicationPolicy of %s but has not specified "
                                     "the property DurationGameplayEffectClass."),
                                *GetActorNameOrLabel(),
                                *StaticEnum<EEffectApplicationPolicy>()
                                     ->GetDisplayNameTextByValue(static_cast<int32>(DurationEffectApplicationPolicy))
                                     .ToString());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }

        if (!IsValid(InfiniteGameplayEffectClass)
            && EEffectApplicationPolicy::DoNotApply != InfiniteEffectApplicationPolicy)
        {
            const auto String =
                FString::Printf(TEXT("Object %s is not an abstract class and has specified an "
                                     "InfiniteEffectApplicationPolicy of %s but has not specified "
                                     "the property InfiniteGameplayEffectClass."),
                                *GetActorNameOrLabel(),
                                *StaticEnum<EEffectApplicationPolicy>()
                                     ->GetDisplayNameTextByValue(static_cast<int32>(InfiniteEffectApplicationPolicy))
                                     .ToString());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }

    return Result;
}
#endif

void AAuraEffectActor::BeginPlay()
{
    Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
    check(GameplayEffectClass);
    if (const auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
    {
        auto Context = ASC->MakeEffectContext();
        Context.AddSourceObject(this);

        // ReSharper disable once CppTooWideScopeInitStatement
        const auto Handle = ASC->MakeOutgoingSpec(GameplayEffectClass, ActorEffectLevel, Context);
        if (Handle.IsValid())
        {
            const auto ActiveGameplayEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*Handle.Data);
            // For GameplayEffects with an Infinite Duration policy, store the resultant handle so that we
            // could later remove the effect via the handle at a later time.
            if (EGameplayEffectDurationType::Infinite == Handle.Data.Get()->Def.Get()->DurationPolicy
                && EEffectRemovalPolicy::DoNotRemove != InfiniteEffectRemovalPolicy)
            {
                // We are caching this here ... even if the effect is not one covered by InfiniteEffectRemovalPolicy
                // ... silly ... but tutorial ...
                ActiveGameplayEffectHandles.Add(ActiveGameplayEffectHandle, ASC);
            }
            if (bDestroyOnEffectRemoval)
            {
                Destroy();
            }
        }
    }
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
    if (EEffectApplicationPolicy::ApplyOnBeginOverlap == InstantEffectApplicationPolicy
        && IsValid(InstantGameplayEffectClass))
    {
        ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
    }
    if (EEffectApplicationPolicy::ApplyOnBeginOverlap == DurationEffectApplicationPolicy
        && IsValid(DurationGameplayEffectClass))
    {
        ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
    }
    if (EEffectApplicationPolicy::ApplyOnBeginOverlap == InfiniteEffectApplicationPolicy
        && IsValid(InfiniteGameplayEffectClass))
    {
        ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
    }
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
    if (EEffectApplicationPolicy::ApplyOnEndOverlap == InstantEffectApplicationPolicy
        && IsValid(InstantGameplayEffectClass))
    {
        ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
    }
    if (EEffectApplicationPolicy::ApplyOnEndOverlap == DurationEffectApplicationPolicy
        && IsValid(DurationGameplayEffectClass))
    {
        ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
    }
    if (EEffectApplicationPolicy::ApplyOnEndOverlap == InfiniteEffectApplicationPolicy
        && IsValid(InfiniteGameplayEffectClass))
    {
        ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
    }

    if (EEffectRemovalPolicy::RemoveOnEndOverlap == InfiniteEffectRemovalPolicy && IsValid(InfiniteGameplayEffectClass))
    {
        // Remove Effect
        if (const auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
        {
            // Really ... iterating over a map to find value matches? A lil insane....
            TArray<FActiveGameplayEffectHandle> HandlesToRemove;
            for (const auto Pair : ActiveGameplayEffectHandles)
            {
                if (ASC == Pair.Value)
                {
                    ASC->RemoveActiveGameplayEffect(Pair.Key, 1);
                    HandlesToRemove.Add(Pair.Key);
                }
            }
            for (const auto& Handle : HandlesToRemove)
            {
                ActiveGameplayEffectHandles.FindAndRemoveChecked(Handle);
            }
        }
    }
}
