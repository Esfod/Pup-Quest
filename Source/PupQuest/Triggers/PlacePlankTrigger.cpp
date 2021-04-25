// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacePlankTrigger.h"
#include "PupQuest/Characters/MainCharacter.h"

APlacePlankTrigger::APlacePlankTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &APlacePlankTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &APlacePlankTrigger::OnOverlapEnd);
}


void APlacePlankTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) {

	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		Main->InPlankTriggerBox = true;
		UE_LOG(LogTemp, Warning, TEXT("You need a plank to get over here"));
		Main->PlacePlankLocation = Location;
		Main->PlacePlankRotation = Rotation;
	}
}

void APlacePlankTrigger::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		Main->InPlankTriggerBox = false;
	}
}

