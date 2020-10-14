// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueAssetTypeActions.h"
#include "DialogueAssetEditorModule.h"
#include "Dialogue.h"


#define LOCTEXT_NAMESPACE "DialogueAssetTypeActions"

FDialogueAssetTypeActions::FDialogueAssetTypeActions()
{
}

FDialogueAssetTypeActions::~FDialogueAssetTypeActions()
{
}

FText FDialogueAssetTypeActions::GetName() const
{
	return NSLOCTEXT("DialogueAssetTypeActions", "DialogueAssetTypeActions", "Dialogue");
}

FColor FDialogueAssetTypeActions::GetTypeColor() const
{
	return FColor::Magenta;
}

UClass* FDialogueAssetTypeActions::GetSupportedClass() const
{
	return UDialogue::StaticClass();
}

void FDialogueAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto MyCustomAsset = Cast<UDialogue>(*ObjIt);
		if (MyCustomAsset != NULL)
		{
			IDialogueAssetEditorModule* CustomAssetEditorModule = &FModuleManager::LoadModuleChecked<IDialogueAssetEditorModule>("DialogueAssetEditor");
			CustomAssetEditorModule->CreateDialogueAssetEditor(Mode, EditWithinLevelEditor, MyCustomAsset);
		}
	}
}

uint32 FDialogueAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

#undef LOCTEXT_NAMESPACE