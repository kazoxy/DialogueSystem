// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueFactory.h"
#include "Dialogue.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "DialogueSystem" 

UDialogueFactory::UDialogueFactory()
{
	// Provide the factory with information about how to handle our asset
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UDialogue::StaticClass();
}

UObject* UDialogueFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UDialogue* Dialogue = NewObject<UDialogue>(InParent, Class, Name, Flags);
	return Dialogue;
}

uint32 UDialogueFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Misc;
}

FText UDialogueFactory::GetDisplayName() const
{
	return LOCTEXT("DialogueText", "Dialogue");
}

FString UDialogueFactory::GetDefaultNewAssetName() const
{
	return FString(TEXT("NewDialogue"));
}

#undef LOCTEXT_NAMESPACE