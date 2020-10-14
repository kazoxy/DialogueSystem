#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UnrealEd.h"
#include "Toolkits/AssetEditorToolkit.h"

DECLARE_LOG_CATEGORY_EXTERN(DialogueAssetEditor, All, All)

class UDialogue;
class IDialogueAssetEditor;

extern const FName DialogueAssetEditorAppIdentifier;

class DIALOGUEASSETEDITOR_API IDialogueAssetEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility
{
public:
	/**
	 * Creates a new custom asset editor.
	 */
	virtual TSharedRef<IDialogueAssetEditor> CreateDialogueAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UDialogue* CustomAsset) = 0;
};