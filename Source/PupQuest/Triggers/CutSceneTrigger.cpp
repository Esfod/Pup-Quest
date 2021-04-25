// Fill out your copyright notice in the Description page of Project Settings.


#include "CutSceneTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "PupQuest/Characters/MainCharacter.h"

ACutSceneTrigger::ACutSceneTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACutSceneTrigger::OnOverlap);
}

void ACutSceneTrigger::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		if (bVideoPlayed == false) {
			//Play video
			/*UGameplayStatics::PlaySoundAtLocation(this, SoundEffect, GetActorLocation());
			bVideoPlayed = true;*/
		}
	}
}