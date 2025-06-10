#pragma once

#include "Abilities/Tasks/AbilityTask.h"
#include "CoreMinimal.h"
#include "AbilityTask_TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature,
                                            const FGameplayAbilityTargetDataHandle&,
                                            DataHandle);

UCLASS()
class AURA_API UAbilityTask_TargetDataUnderMouse : public UAbilityTask
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable,
              Category = "Aura|Ability|Tasks",
              meta = (DisplayName = "Target Data Under Mouse",
                      HidePin = "OwningAbility",
                      DefaultToSelf = "OwningAbility",
                      BlueprintInternalUseOnly = "true"))
    static UAbilityTask_TargetDataUnderMouse* CreateTargetDataUnderMouseProxy(UGameplayAbility* OwningAbility);

    UPROPERTY(BlueprintAssignable)
    FMouseTargetDataSignature ValidData;

private:
    virtual void Activate() override;

    void SendMouseCursorData() const;

    void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
