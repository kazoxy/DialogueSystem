// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UDialogue;

/**
 * 
 */
class DIALOGUEASSETEDITOR_API IDialogueAssetEditor : public FAssetEditorToolkit
{
public:
	IDialogueAssetEditor();
	~IDialogueAssetEditor();

	virtual UDialogue* GetDialogueAsset() const = 0;

	virtual void SetDialogueAsset(UDialogue* InCustomAsset) = 0;
};
