

using UnrealBuildTool;

public class AuraTarget : TargetRules
{
    public AuraTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;

        ExtraModuleNames.AddRange(new string[] { "Aura" });
    }
}
