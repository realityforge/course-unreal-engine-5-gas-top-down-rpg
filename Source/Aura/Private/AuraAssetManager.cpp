#include "AuraAssetManager.h"

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
}
