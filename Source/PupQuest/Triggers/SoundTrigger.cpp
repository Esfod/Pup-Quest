// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "PupQuest/Characters/MainCharacter.h"

ASoundTrigger::ASoundTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ASoundTrigger::OnOverlap);
}

void ASoundTrigger::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		if (bSoundPlayed == false) {
			UGameplayStatics::PlaySoundAtLocation(this, SoundEffect, GetActorLocation());
			bSoundPlayed = true;
		}
	}
}