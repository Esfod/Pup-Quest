// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEndTrigger.h"
#include "PupQuest/Characters/MainCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "PupQuest/PupQuestGameInstance.h"

ALevelEndTrigger::ALevelEndTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ALevelEndTrigger::OnOverlap);
}

void ALevelEndTrigger::ChangeLevel() {
	UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
	GameInstance->NewSpawn = false;
	GameInstance->bGameStarted = true;
	UGameplayStatics::OpenLevel(this, NextLevel, false);
}


void ALevelEndTrigger::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
		ChangeLevel();
}