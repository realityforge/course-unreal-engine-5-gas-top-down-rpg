#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Logging/StructuredLog.h"
#include "Misc/DataValidation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraProjectileSpell)

#if WITH_EDITOR
EDataValidationResult UAuraProjectileSpell::IsDataValid(FDataValidationContext& Context) const
{
    auto Result = CombineDataValidationResults(Super::IsDataValid(Context), EDataValidationResult::Valid);

    if (!GetClass()->HasAnyClassFlags(CLASS_Abstract))
    {
        if (!IsValid(ProjectileClass))
        {
            const auto String =
                FString::Printf(TEXT("Object %s is not abstract but has not specified the ProjectileClass property"),
                                *GetName());
            Context.AddError(FText::FromString(String));
            Result = EDataValidationResult::Invalid;
        }
    }

    return Result;
}
#endif

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    if (HasAuthority(&ActivationInfo))
    {
        const auto AvatarActor = GetAvatarActorFromActorInfo();
        if (const auto CombatInterface = Cast<ICombatInterface>(AvatarActor))
        {
            const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

            FTransform SpawnTransform;
            SpawnTransform.SetLocation(SocketLocation);

            // TODO: Calculate the Projectile Rotation

            const auto Owner = GetOwningActorFromActorInfo();
            const auto Projectile =
                GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,
                                                                SpawnTransform,
                                                                Owner,
                                                                Cast<APawn>(Owner),
                                                                ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

            // TODO: Apply Effect for Damage? Apply Cue for Spawn?

            if (Projectile)
            {
                Projectile->FinishSpawning(SpawnTransform);
            }
            else
            {
                UE_LOGFMT(LogTemp,
                          Warning,
                          "Ability {Name} failed to create Projectile of type {ProjectileClass} with Owner {Owner}",
                          GetNameSafe(ProjectileClass),
                          GetNameSafe(Owner));
            }
        }
        else
        {
            UE_LOGFMT(LogTemp,
                      Warning,
                      "Ability {Name} activated from AvatarActor {AvatarActor} "
                      "which does not implement ICombatInterface",
                      GetName(),
                      GetNameSafe(AvatarActor));
        }
    }
}
