#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FAuraInputAction
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> InputAction{ nullptr };

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Input"))
    FGameplayTag InputTag{ FGameplayTag::EmptyTag };
};

UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
    GENERATED_BODY()

    /** Map InputAction to InputTag. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TArray<FAuraInputAction> Actions;

public:
    const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
};
