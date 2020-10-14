// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Dialogue.generated.h"

class UDialogueComponent;
class UWorld;

UCLASS(Blueprintable, BlueprintType, abstract, DefaultToInstanced, EditInlineNew)
class DIALOGUESYSTEM_API UDialogueCondition : public UObject
{
	GENERATED_BODY()

public:
	UDialogueCondition();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue|Condition")
		bool IsConditionMet(APlayerController* Player, UDialogueComponent* DialogueComponent);

	virtual UWorld* GetWorld() const override;
};

UCLASS(Blueprintable, BlueprintType, abstract, DefaultToInstanced, EditInlineNew)
class DIALOGUESYSTEM_API UDialogueEvent : public UObject
{
	GENERATED_BODY()

public:
	UDialogueEvent();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue|Event")
		void TriggerEvent(APlayerController* Player, UDialogueComponent* DialogueComponent);

	virtual UWorld* GetWorld() const override;
};

UENUM(BlueprintType)
enum class DialogueNodeType : uint8
{
	Player UMETA(DisplayName = "Player"),
	NPC UMETA(DisplayName = "NPC"),
	Branch UMETA(DisplayName = "Branch"),
	Choice UMETA(DisplayName = "Choice"),
	Option UMETA(DisplayName = "Option")
};

USTRUCT(BlueprintType)
struct FDialogueInfoId
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	DialogueNodeType DialogueNodeType;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	int32 NodeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	FDialogueInfoId InfoId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	TArray<int32> Links;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Dialogue Node")
	TArray<UDialogueCondition*> Conditions;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Dialogue Node")
	TArray<UDialogueEvent*> Events;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	FVector2D Coordinates;
};

USTRUCT(BlueprintType)
struct FDialogueInfoPlayerNode
{
	GENERATED_USTRUCT_BODY()

};

USTRUCT(BlueprintType)
struct FDialogueInfoNPCNode
{
	GENERATED_USTRUCT_BODY()

};

USTRUCT(BlueprintType)
struct FDialogueInfoBranchNode
{
	GENERATED_USTRUCT_BODY()

};

USTRUCT(BlueprintType)
struct FDialogueInfoChoiceNode
{
	GENERATED_USTRUCT_BODY()

};

USTRUCT(BlueprintType)
struct FDialogueInfoOptionNode
{
	GENERATED_USTRUCT_BODY()

};

/**
 * 
 */
UCLASS(BlueprintType)
class DIALOGUESYSTEM_API UDialogue : public UObject
{
	GENERATED_BODY()
	
public:

	UDialogue();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueNode> Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<int32, FDialogueInfoPlayerNode> PlayerNodesInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<int32, FDialogueInfoNPCNode> NPCNodesInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<int32, FDialogueInfoBranchNode> BranchNodesInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<int32, FDialogueInfoChoiceNode> ChoiceNodesInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<int32, FDialogueInfoOptionNode> OptionNodesInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	class UGameInstance * PersistentGameInstance;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AssignPersistentOuter(class UGameInstance * inGameInstance);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void CleanOuter();

	virtual UWorld* GetWorld() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 CurrentNodeId;

	bool isLinking;
	FVector2D LinkingCoords;
	int32 LinkingFromIndex;
	int NextNodeId;
};
