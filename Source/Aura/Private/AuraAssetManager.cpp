#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"

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

    // TODO: This is only used for initializing GameplayTags and it would be better to use the
    //       technique outlined in AuraGameplayTags.h. However keeping this class for the sake
    //       of tutorial...
    FAuraGameplayTags::InitializeNativeGameplayTags();
}
