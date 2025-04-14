#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    AAuraCharacterBase();

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

protected:
    virtual void BeginPlay() override;

    /** Mesh representing the weapon the character is carrying. */
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon{ nullptr };
};
