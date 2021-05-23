// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointHitBox.h"
#include "PupQuest/Characters/MainCharacter.h"
#include "PupQuest/PupQuestGameInstance.h"


ACheckpointHitBox::ACheckpointHitBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ACheckpointHitBox::OnOverlap);
}

void ACheckpointHitBox::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {

	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
		GameInstance->RespawnPoint = FVector(Location);//The players respawn point is the given location in the editor
		GameInstance->NewSpawn = true;//This makes sure 
		//UE_LOG(LogTemp, Warning, TEXT("New spawn point"));
	}
}