#include "UI/Widget/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

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
        .AddLambda([this](const auto& Data) { OnHealthChanged.Broadcast(Data.NewValue); });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
        .AddLambda([this](const auto& Data) { OnMaxHealthChanged.Broadcast(Data.NewValue); });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
        .AddLambda([this](const auto& Data) { OnManaChanged.Broadcast(Data.NewValue); });
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
        .AddLambda([this](const auto& Data) { OnMaxManaChanged.Broadcast(Data.NewValue); });

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
