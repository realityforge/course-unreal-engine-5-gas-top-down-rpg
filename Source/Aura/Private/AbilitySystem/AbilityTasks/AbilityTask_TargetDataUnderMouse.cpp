#include "AbilitySystem/AbilityTasks/AbilityTask_TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"
#include "Logging/StructuredLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityTask_TargetDataUnderMouse)

UAbilityTask_TargetDataUnderMouse*
UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouseProxy(UGameplayAbility* OwningAbility)
{
    return NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwningAbility);
}

void UAbilityTask_TargetDataUnderMouse::Activate()
{
    if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
    {
        SendMouseCursorData();
    }
    else
    {
        const auto SpecHandle = GetAbilitySpecHandle();
        const auto PredictionKey = GetActivationPredictionKey();
        // This is executing on the server so we need to listen for target data being sent from the client.
        AbilitySystemComponent->AbilityTargetDataSetDelegate(SpecHandle, PredictionKey)
            .AddUObject(this, &UAbilityTask_TargetDataUnderMouse::OnTargetDataReplicatedCallback);
        // If the RPC for target data has completed and the data is already on the server then invoke the delegate
        const bool bDelegateInvoked =
            AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, PredictionKey);
        if (!bDelegateInvoked)
        {
            // If the RPC is still in flight then the ability task should wait for remote player data.
            SetWaitingOnRemotePlayerData();
        }
    }
}

void UAbilityTask_TargetDataUnderMouse::SendMouseCursorData() const
{
    // Use RAII pattern to manage a prediction window
    FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

    if (const auto PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get())
    {
        FHitResult CursorHit;
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

        const auto DataHandle = new FGameplayAbilityTargetData_SingleTargetHit(CursorHit);

        const auto TargetDataHandle = FGameplayAbilityTargetDataHandle{ DataHandle };
        AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
                                                              GetActivationPredictionKey(),
                                                              TargetDataHandle,
                                                              FGameplayTag::EmptyTag,
                                                              AbilitySystemComponent->ScopedPredictionKey);

        if (ShouldBroadcastAbilityTaskDelegates())
        {
            ValidData.Broadcast(TargetDataHandle);
        }
    }
    else
    {
        UE_LOGFMT(LogTemp,
                  Warning,
                  "UAbilityTask_TargetDataUnderMouse but owning Character has a null PlayerController");
    }
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAbilityTask_TargetDataUnderMouse::OnTargetDataReplicatedCallback(
    const FGameplayAbilityTargetDataHandle& DataHandle,
    [[maybe_unused]] FGameplayTag ActivationTag)
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(FGameplayAbilityTargetDataHandle{ DataHandle });
    }
}
