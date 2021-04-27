// Fill out your copyright notice in the Description page of Project Settings.


#include "CloseDoorTriggerBox.h"
#include "PupQuest/Characters/MainCharacter.h"
#include "PupQuest/Actors/DoorActors/BaseDoorActor.h"

ACloseDoorTriggerBox::ACloseDoorTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ACloseDoorTriggerBox::OnOverlap);

}

void ACloseDoorTriggerBox::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{	if(DoorToClose)
			DoorToClose->CloseDoor();
	}
}
