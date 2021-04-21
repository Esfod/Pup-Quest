// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEndTrigger.h"
#include "Characters/MainCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

ALevelEndTrigger::ALevelEndTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ALevelEndTrigger::OnOverlap);
}

void ALevelEndTrigger::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		UGameplayStatics::OpenLevel(this, NextLevel, false);
	}
}