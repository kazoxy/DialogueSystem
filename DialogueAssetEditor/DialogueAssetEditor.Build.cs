using UnrealBuildTool;

public class DialogueAssetEditor : ModuleRules
{
    public DialogueAssetEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        PublicDependencyModuleNames.AddRange(new string[] { "Project", "DialogueSystem" });

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Json",
				"JsonUtilities",
                "Slate",
                "SlateCore",
                "UnrealEd", // for FAssetEditorManager
                "KismetWidgets",
                "Kismet",  // for FWorkflowCentricApplication
                "PropertyEditor",
                "RenderCore",
                "ContentBrowser",
                "WorkspaceMenuStructure",
                "EditorStyle",
                "EditorWidgets",
                "Projects",
                "AssetRegistry",
                "GraphEditor"
        
                // ... add private dependencies that you statically link with here ...	
	        }
        );

        PublicIncludePaths.AddRange(
            new string[]
            {
                "DialogueAssetEditor/Public"
            });

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "DialogueAssetEditor/Private"
            });

        PrivateIncludePathModuleNames.AddRange(
            new string[]
            {
                "Settings",
                "IntroTutorials",
                "AssetTools",
                "LevelEditor"
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                "AssetTools"
            }
        );
    }
}
