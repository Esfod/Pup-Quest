// Fill out your copyright notice in the Description page of Project Settings.


#include "CutSceneTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "PupQuest/Characters/MainCharacter.h"
#include "MediaPlayer.h"

ACutSceneTrigger::ACutSceneTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACutSceneTrigger::OnOverlap);
}

void ACutSceneTrigger::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		if (bVideoPlayed == false) {			
			bVideoPlayed = true;
			UE_LOG(LogTemp, Warning, TEXT("Video playing"));
			Video->Play();

			//Video->GetTime();Use to tell when widget should close
		}
	}
}