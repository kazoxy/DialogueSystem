#include "DialogueAssetEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
//#include "IToolkit.h"
#include "Dialogue.h"
#include "DialogueAssetEditor.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "DialogueAssetTypeActions.h"
#include "DialogueEditorStyle.h"

DEFINE_LOG_CATEGORY(DialogueAssetEditor);

#define LOCTEXT_NAMESPACE "DialogueAssetEditor"

const FName DialogueAssetEditorAppIdentifier = FName(TEXT("DialogueAssetEditorApp"));

/**
 * Custom Asset editor module
 */
class DIALOGUEASSETEDITOR_API FDialogueAssetEditorModule : public IDialogueAssetEditorModule
{
public:
	FDialogueAssetEditorModule() { }

	/** Gets the extensibility managers for outside entities to extend custom asset editor's menus and toolbars */

	//IHasMenuExtensibility
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override { return MenuExtensibilityManager; }
	//~IHasMenuExtensibility

	//IHasToolBarExtensibility
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }
	//~IHasToolBarExtensibility

	
	//IModuleInterface
	/**
	* Called right after the module DLL has been loaded and the module object has been created
	*/
	virtual void StartupModule() override
	{
		// registers the style (sets icons)
		FDialogueEditorStyle::Initialize();
		
		// Create new extensibility managers for our menu and toolbar
		MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
		ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		RegisterAssetTypeAction(AssetTools, MakeShareable(new FDialogueAssetTypeActions()));

		UE_LOG(DialogueAssetEditor, Warning, TEXT("DialogueAssetEditor: Log Started"));
	}

	/**
	* Called before the module is unloaded, right before the module object is destroyed.
	*/
	virtual void ShutdownModule() override
	{
		// Reset our existing extensibility managers
		MenuExtensibilityManager.Reset();
		ToolBarExtensibilityManager.Reset();

		if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
		{
			// Unregister our custom created assets from the AssetTools
			IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
			for (int32 i = 0; i < CreatedAssetTypeActions.Num(); ++i)
			{
				AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[i].ToSharedRef());
			}
		}
		
		CreatedAssetTypeActions.Empty();

		UE_LOG(DialogueAssetEditor, Warning, TEXT("DialogueAssetEditor: Log Ended"));
	}
	//~IModuleInterface

	/**
	* Creates a new custom asset editor for a MyCustomAsset
	*/
	virtual TSharedRef<IDialogueAssetEditor> CreateDialogueAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UDialogue* DialogueAsset) override
	{
		// Initialize and spawn a new custom asset editor with the provided parameters
		TSharedRef<FDialogueAssetEditor> NewDialogueAssetEditor(new FDialogueAssetEditor());
		NewDialogueAssetEditor->InitDialogueAssetEditor(Mode, InitToolkitHost, DialogueAsset);
		return NewDialogueAssetEditor;
	}

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions(Action);
		CreatedAssetTypeActions.Add(Action);
	}

	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

private:
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
};

IMPLEMENT_GAME_MODULE(FDialogueAssetEditorModule, DialogueAssetEditor);

#undef LOCTEXT_NAMESPACE