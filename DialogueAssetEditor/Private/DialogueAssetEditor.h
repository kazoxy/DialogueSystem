// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"
#include "DialogueAssetEditorInterface.h"

class IDetailsView;
class SDockableTab;
class UDialogue;

/**
 * 
 */
class DIALOGUEASSETEDITOR_API FDialogueAssetEditor : public IDialogueAssetEditor
{
public:
	FDialogueAssetEditor();
	virtual ~FDialogueAssetEditor();


	//FAssetEditorToolkit
	// This function creates tab spawners on editor initialization
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	// This function unregisters tab spawners on editor initialization
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	// This method decides how the custom asset editor will be initialized
	void InitDialogueAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UDialogue* InCustomAsset);
	//~FAssetEditorToolkit

	//IToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override { return true; }
	//~IToolkit

	//IDialogueAssetEditor
	virtual UDialogue* GetDialogueAsset() const override;
	virtual void SetDialogueAsset(UDialogue* InCustomAsset) override;
	//~IDialogueAssetEditor

private:
	/** Create the properties tab and its content */
	TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);

	TSharedRef<SDockTab> SpawnViewportTab(const FSpawnTabArgs& Args);

	/** Dockable tab for properties */
	TSharedPtr< SDockableTab > PropertiesTab;

	/** Dockable tab for viewport */
	TSharedPtr< SDockableTab > ViewportTab;

	/** Details view */
	TSharedPtr<class IDetailsView> DetailsView;

	/** Viewport */
	TSharedPtr<class SDialogueViewportWidget> DialogueViewportWidget;

	/** Name */
	static const FName ToolkitFName;

	/**	The tab ids for properties */
	static const FName PropertiesTabId;

	/**	The tab ids for viewport */
	static const FName ViewportTabId;

	/** The Custom Asset open within this editor */
	UDialogue* DialogueAsset;
};
