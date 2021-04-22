// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointHitBox.h"
#include "Characters/MainCharacter.h"
#include "PupQuestGameInstance.h"


ACheckpointHitBox::ACheckpointHitBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ACheckpointHitBox::OnOverlap);

}

void ACheckpointHitBox::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {

	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
		GameInstance->RespawnPoint = FVector(Location);
		GameInstance->NewSpawn = true;
		UE_LOG(LogTemp, Warning, TEXT("New spawn point"));
	}
}