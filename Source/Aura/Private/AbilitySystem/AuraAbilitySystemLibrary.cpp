#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAbilitySystemLibrary)

AAuraPlayerController* UAuraAbilitySystemLibrary::GetAuraPlayerController(const UObject* WorldContextObject)
{
    return Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}
