#include "DialogueEditorStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"


#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

FString FDialogueEditorStyle::RootToContentDir(const ANSICHAR* RelativePath, const TCHAR* Extension)
{
	static FString ContentDir = FPaths::ProjectContentDir();
	return (ContentDir / "DialogueSystem" / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FDialogueEditorStyle::StyleSet = nullptr;
TSharedPtr< ISlateStyle > FDialogueEditorStyle::Get() { return StyleSet; }


FName FDialogueEditorStyle::GetStyleSetName()
{
	static FName DialogueEditorStyleName(TEXT("DialogueEditorStyle"));
	return DialogueEditorStyleName;
}

void FDialogueEditorStyle::Initialize()
{
	 //Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	{
		StyleSet->Set("NodeStyle", new BOX_BRUSH("Node", FMargin(5.f / 138.f, 5.f / 56.f, 5.f / 138.f, 5.f / 56.f)));
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
};

#undef BOX_BRUSH
#undef IMAGE_BRUSH


void FDialogueEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}
