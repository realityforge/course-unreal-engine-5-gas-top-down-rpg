#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Misc/DataValidation.h"

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
        if (!IsValid(InstanceGameplayEffectClass) && !IsValid(DurationGameplayEffectClass))
        {
            const auto String = FString::Printf(TEXT("Object %s is not an abstract class but has not specified "
                                                     "either of the properties InstanceGameplayEffectClass or "
                                                     "DurationGameplayEffectClass. At least one must be specified"),
                                                *GetActorNameOrLabel());
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

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor,
                                           const TSubclassOf<UGameplayEffect> GameplayEffectClass) const
{
    check(GameplayEffectClass);
    if (const auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
    {
        auto Context = ASC->MakeEffectContext();
        Context.AddSourceObject(this);

        // ReSharper disable once CppTooWideScopeInitStatement
        const auto Handle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, Context);
        if (Handle.IsValid())
        {
            ASC->ApplyGameplayEffectSpecToSelf(*Handle.Data);
        }
    }
}
