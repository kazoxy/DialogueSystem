// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class DIALOGUEASSETEDITOR_API FDialogueAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FDialogueAssetTypeActions();
	~FDialogueAssetTypeActions();

	//IAssetTypeActions
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;
	//~IAssetTypeActions
};
