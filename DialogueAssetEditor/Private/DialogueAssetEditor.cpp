// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueAssetEditor.h"
#include "Modules/ModuleManager.h"
#include "EditorStyleSet.h"
#include "Widgets/Docking/SDockTab.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Editor.h"
//#include "AssetEditorToolkit.h"
#include "DialogueAssetEditorModule.h"

#include "DialogueViewportWidget.h"

#define LOCTEXT_NAMESPACE "DialogueAssetEditor"

const FName FDialogueAssetEditor::ToolkitFName(TEXT("DialogueAssetEditor"));
const FName FDialogueAssetEditor::PropertiesTabId(TEXT("DialogueAssetEditor_Properties"));
const FName FDialogueAssetEditor::ViewportTabId(TEXT("DialogueAssetEditor_Viewport"));

FDialogueAssetEditor::FDialogueAssetEditor()
{
}

FDialogueAssetEditor::~FDialogueAssetEditor()
{
	// On destruction we reset our tab and details view 
	DetailsView.Reset();
	PropertiesTab.Reset();
}

void FDialogueAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	// Add a new workspace menu category to the tab manager
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_DialogueAssetEditor", "Dialogue Asset Editor"));

	// We register the tab manager to the asset editor toolkit so we can use it in this editor
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	// Register the properties tab spawner within our tab manager
	// We provide the function with the identiefier for this tab and a shared pointer to the
	// SpawnPropertiesTab function within this editor class
	// Additionaly, we provide a name to be displayed, a category and the tab icon
	InTabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FDialogueAssetEditor::SpawnViewportTab))
		.SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FDialogueAssetEditor::SpawnPropertiesTab))
		.SetDisplayName(LOCTEXT("DetailsTabLabel", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FDialogueAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	// Unregister the tab manager from the asset editor toolkit
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	// Unregister our custom tab from the tab manager, making sure it is cleaned up when the editor gets destroyed
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
	InTabManager->UnregisterTabSpawner(ViewportTabId);
}

void FDialogueAssetEditor::InitDialogueAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UDialogue* InCustomAsset)
{
	// Cache some values that will be used for our details view arguments
	const bool bIsUpdatable = false;
	const bool bAllowFavorites = true;
	const bool bIsLockable = false;

	// Set this InCustomAsset as our editing asset
	SetDialogueAsset(InCustomAsset);

	// Retrieve the property editor module and assign properties to DetailsView
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(bIsUpdatable, bIsLockable, true, FDetailsViewArgs::ObjectsUseNameArea, false);
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// Create the layout of our custom asset editor
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_DialogueAssetEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->SetHideTabWell(true)
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					(
						FTabManager::NewStack()
						->SetHideTabWell(true)
						->AddTab(PropertiesTabId, ETabState::OpenedTab)
					)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	// Initialize our custom asset editor
	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		DialogueAssetEditorAppIdentifier,
		StandaloneDefaultLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		(UObject*)InCustomAsset);

	RegenerateMenusAndToolbars();

	// Set the asset we are editing in the details view
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject((UObject*)DialogueAsset);
	}
}

FName FDialogueAssetEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FDialogueAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Custom Asset Editor");
}

FText FDialogueAssetEditor::GetToolkitName() const
{
	return LOCTEXT("Name", "DialogueAssetEditor");
}

FText FDialogueAssetEditor::GetToolkitToolTipText() const
{
	return LOCTEXT("ToolTip", "Custom Asset Editor");
}

FString FDialogueAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "AnimationDatabase ").ToString();
}

FLinearColor FDialogueAssetEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Red;
}

UDialogue* FDialogueAssetEditor::GetDialogueAsset() const
{
	return DialogueAsset;
}

void FDialogueAssetEditor::SetDialogueAsset(UDialogue* InCustomAsset)
{
	DialogueAsset = InCustomAsset;
}

TSharedRef<SDockTab> FDialogueAssetEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args)
{
	// Make sure we have the correct tab id
	check(Args.GetTabId() == PropertiesTabId);

	// Return a new slate dockable tab that contains our details view
	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
		.Label(LOCTEXT("GenericDetailsTitle", "Details"))
		.TabColorScale(GetTabColorScale())
		[
			// Provide the details view as this tab its content
			DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FDialogueAssetEditor::SpawnViewportTab(const FSpawnTabArgs & Args)
{
	// Make sure we have the correct tab id
	check(Args.GetTabId() == ViewportTabId);

	// Return a new slate dockable tab that contains our details view
	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
		.Label(LOCTEXT("GenericViewportTitle", "Viewport"))
		.TabColorScale(GetTabColorScale())
		[
			SAssignNew(DialogueViewportWidget, SDialogueViewportWidget, SharedThis(this))
			.Dialogue(DialogueAsset)
		];
}

#undef LOCTEXT_NAMESPACE