#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"

AAuraPlayerController* UAuraAbilitySystemLibrary::GetAuraPlayerController(const UObject* WorldContextObject)
{
    return Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}
