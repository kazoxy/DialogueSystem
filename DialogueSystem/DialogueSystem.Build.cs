using UnrealBuildTool;

public class DialogueSystem : ModuleRules
{
    public DialogueSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        PublicDependencyModuleNames.AddRange(new string[] { "Project" });

        PublicIncludePaths.AddRange(
            new string[]
            {
                "DialogueSystem/Public"
            });

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "DialogueSystem/Private"
            });
    }
}
