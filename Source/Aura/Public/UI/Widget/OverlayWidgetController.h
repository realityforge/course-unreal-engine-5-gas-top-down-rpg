#pragma once

#include "AbilitySystem/AuraAttributeSet.h"
#include "CoreMinimal.h"
#include "UI/Widget/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

UCLASS(Abstract, BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
    GENERATED_BODY()

public:
    virtual void BroadcastInitialValues() override;
    virtual void BindCallbacksToDependencies() override;

    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnHealthChangedSignature OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnMaxHealthChangedSignature OnMaxHealthChanged;

private:
    void OnHealthChange(const FOnAttributeChangeData& OnAttributeChangeData) const;
    void OnMaxHealthChange(const FOnAttributeChangeData& OnAttributeChangeData) const;

    UAuraAttributeSet* GetAuraAttributeSet() const;
};
