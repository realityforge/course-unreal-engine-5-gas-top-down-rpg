#pragma once

#include "AbilitySystem/AuraAttributeSet.h"
#include "CoreMinimal.h"
#include "UI/Widget/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Message"))
    FGameplayTag MessageTag{ FGameplayTag::EmptyTag };

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText Message{};

    /** A Widget we can create and add to viewport on receiving the MessageTag. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UAuraUserWidget> MessageWidget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UTexture2D> Image{ nullptr };
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, WidgetRow);

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

    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnManaChangedSignature OnManaChanged;

    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnMaxManaChangedSignature OnMaxManaChanged;

    UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
    FMessageWidgetRowSignature MessageWidgetRow;

private:
    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = "Widget Data",
              meta = (AllowPrivateAccess = true, RequiredAssetDataTags = "RowStructure=/Script/Aura.UIWidgetRow"))
    TObjectPtr<UDataTable> MessageWidgetDataTable{ nullptr };

    void OnHealthChange(const FOnAttributeChangeData& OnAttributeChangeData) const;
    void OnMaxHealthChange(const FOnAttributeChangeData& OnAttributeChangeData) const;
    void OnManaChange(const FOnAttributeChangeData& OnAttributeChangeData) const;
    void OnMaxManaChange(const FOnAttributeChangeData& OnAttributeChangeData) const;

    UAuraAttributeSet* GetAuraAttributeSet() const;

    template <typename T>
    static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
    return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
