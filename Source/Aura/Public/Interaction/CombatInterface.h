#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
    GENERATED_BODY()
};

class AURA_API ICombatInterface
{
    GENERATED_BODY()

public:
    // This is implemented as part of the interface rather than as an attribute for no reason other than
    // the tutorial wanted to have an excuse to use MMC (Modifier Magnitude Calculation) class as alternate
    // way to experiment with calculating magnitudes.
    virtual int32 GetPlayerLevel();
};
