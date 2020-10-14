// Fill out your copyright notice in the Description page of Project Settings.

#include "Dialogue.h"

UDialogueCondition::UDialogueCondition()
{

}

bool UDialogueCondition::IsConditionMet_Implementation(APlayerController * Player, UDialogueComponent * DialogueComponent)
{
	return true;
}

UWorld* UDialogueCondition::GetWorld() const
{
	UDialogue * outerDialogue = GetTypedOuter<UDialogue>();

	if (outerDialogue)
	{
		return outerDialogue->GetWorld();
	}
	else
	{
		return nullptr;
	}
}

UDialogueEvent::UDialogueEvent()
{

}

UWorld* UDialogueEvent::GetWorld() const
{
	UDialogue * outerDialogue = GetTypedOuter<UDialogue>();

	if (outerDialogue)
	{
		return outerDialogue->GetWorld();
	}
	else
	{
		return nullptr;
	}
}

UDialogue::UDialogue()
{
}

void UDialogue::AssignPersistentOuter(UGameInstance * inGameInstance)
{
	PersistentGameInstance = inGameInstance;
}

void UDialogue::CleanOuter()
{
	PersistentGameInstance = nullptr;
}

UWorld* UDialogue::GetWorld() const
{
	return PersistentGameInstance->GetWorld();
}