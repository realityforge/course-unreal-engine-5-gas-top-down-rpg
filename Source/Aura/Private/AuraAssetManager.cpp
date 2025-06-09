#include "AuraAssetManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraAssetManager)

UAuraAssetManager& UAuraAssetManager::Get()
{
    check(GEngine);

    const auto AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
    check(AuraAssetManager);
    return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();
    // This does not seem to be needed anymore?
    // UAbilitySystemGlobals::Get().InitGlobalData();
}
