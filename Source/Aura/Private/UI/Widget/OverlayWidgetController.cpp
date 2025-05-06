#include "UI/Widget/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::OnHealthChange(const FOnAttributeChangeData& OnAttributeChangeData) const
{
    OnHealthChanged.Broadcast(OnAttributeChangeData.NewValue);
}

void UOverlayWidgetController::OnMaxHealthChange(const FOnAttributeChangeData& OnAttributeChangeData) const
{
    OnMaxHealthChanged.Broadcast(OnAttributeChangeData.NewValue);
}

void UOverlayWidgetController::OnManaChange(const FOnAttributeChangeData& OnAttributeChangeData) const
{
    OnManaChanged.Broadcast(OnAttributeChangeData.NewValue);
}

void UOverlayWidgetController::OnMaxManaChange(const FOnAttributeChangeData& OnAttributeChangeData) const
{
    OnMaxManaChanged.Broadcast(OnAttributeChangeData.NewValue);
}

UAuraAttributeSet* UOverlayWidgetController::GetAuraAttributeSet() const
{
    check(AttributeSet.Get());
    return CastChecked<UAuraAttributeSet>(AttributeSet.Get());
}

void UOverlayWidgetController::BroadcastInitialValues()
{
    const auto AuraAttributeSet = GetAuraAttributeSet();
    OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
    OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
    OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
    OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
    const auto AuraAttributeSet = GetAuraAttributeSet();
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
        .AddUObject(this, &UOverlayWidgetController::OnHealthChange);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
        .AddUObject(this, &UOverlayWidgetController::OnMaxHealthChange);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
        .AddUObject(this, &UOverlayWidgetController::OnManaChange);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
        .AddUObject(this, &UOverlayWidgetController::OnMaxManaChange);

    if (const auto ASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
    {
        ASC->EffectAssetTags.AddLambda([this](const auto& AssetTags) {
            const auto Tag_Message = FGameplayTag::RequestGameplayTag(FName("Message"));
            for (const auto& Tag : AssetTags)
            {
                // ReSharper disable once CppTooWideScopeInitStatement
                if (Tag.MatchesTag(Tag_Message))
                {
                    const auto Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
                    MessageWidgetRow.Broadcast(*Row);
                }
            }
        });
    }
}
