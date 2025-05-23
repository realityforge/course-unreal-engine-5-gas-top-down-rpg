﻿#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeDef
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Attributes"))
    FGameplayTag Tag{ FGameplayTag::EmptyTag };

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText Name{};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText Description{};

    bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FAuraAttributeDef Attribute;

    UPROPERTY(BlueprintReadOnly)
    float Value{ 0.f };
};

UCLASS(Const)
class AURA_API UAttributeInfo : public UDataAsset
{
    GENERATED_BODY()

public:
    FAuraAttributeDef FindAttributeDefForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = true) const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "{Name} {Tag}"))
    TArray<FAuraAttributeDef> Attributes;

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
};
