#include "DialogueSystem.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FDialogueSystemModule, DialogueSystem);

DEFINE_LOG_CATEGORY(DialogueSystem);

#define LOCTEXT_NAMESPACE "DialogueSystem"

void FDialogueSystemModule::StartupModule()
{
	UE_LOG(DialogueSystem, Warning, TEXT("DialogueSystem: Log Started"));
}

void FDialogueSystemModule::ShutdownModule()
{
	UE_LOG(DialogueSystem, Warning, TEXT("DialogueSystem: Log Ended"));
}

#undef LOCTEXT_NAMESPACE