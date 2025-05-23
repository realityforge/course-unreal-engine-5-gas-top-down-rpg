using UnrealBuildTool;

public class Aura : ModuleRules
{
    public Aura(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Aeon", "Core", "CoreUObject", "Engine", "InputCore",
                                                     "GameplayAbilities", "ModularGasGameplayActors" });
        PrivateDependencyModuleNames.AddRange(new[] { "EnhancedInput", "GameplayTags", "GameplayTasks" });
    }
}
