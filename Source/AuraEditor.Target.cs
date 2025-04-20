

using UnrealBuildTool;

public class AuraEditorTarget : TargetRules
{
    public AuraEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;

        ExtraModuleNames.AddRange(new string[] { "Aura" });
    }
}
