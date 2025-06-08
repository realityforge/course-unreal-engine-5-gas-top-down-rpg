#include "AbilitySystem/AbilityTasks/AbilityTask_TargetDataUnderMouse.h"
#include "Logging/StructuredLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityTask_TargetDataUnderMouse)

UAbilityTask_TargetDataUnderMouse*
UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouseProxy(UGameplayAbility* OwningAbility)
{
    return NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwningAbility);
}

void UAbilityTask_TargetDataUnderMouse::Activate()
{
    if (const auto PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get())
    {
        FHitResult CursorHit;
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
        ValidData.Broadcast(CursorHit.Location);
    }
    else
    {
        UE_LOGFMT(LogTemp,
                  Warning,
                  "UAbilityTask_TargetDataUnderMouse but owning Character has a null PlayerController");
    }
}
