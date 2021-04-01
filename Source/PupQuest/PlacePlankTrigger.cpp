// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacePlankTrigger.h"
#include "Characters/MainCharacter.h"

APlacePlankTrigger::APlacePlankTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &APlacePlankTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &APlacePlankTrigger::OnOverlapEnd);
}


void APlacePlankTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) {

	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		Main->InTriggerBox = true;

	}
}

void APlacePlankTrigger::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		Main->InTriggerBox = false;
	}
}

