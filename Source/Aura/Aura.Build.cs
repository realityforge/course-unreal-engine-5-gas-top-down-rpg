using UnrealBuildTool;

public class Aura : ModuleRules
{
    public Aura(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(
            new[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayAbilities" });
        PrivateDependencyModuleNames.AddRange(new[] { "EnhancedInput", "GameplayTags", "GameplayTasks" });
    }
}
