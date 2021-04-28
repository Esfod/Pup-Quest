// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorClose_TriggerBox.h"

#include "PupQuest/Actors/DoorActors/BaseDoorActor.h"
#include "PupQuest/Characters/MainCharacter.h"


ADoorClose_TriggerBox::ADoorClose_TriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ADoorClose_TriggerBox::OnOverlap);
}

void ADoorClose_TriggerBox::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Hallo spelar går i gjennom"));
		if(DoorToClose)
			DoorToClose->CloseDoor();
	}
}
