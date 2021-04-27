// Fill out your copyright notice in the Description page of Project Settings.


#include "WinningTrigger.h"
#include "PupQuest/Characters/MainCharacter.h"

AWinningTrigger::AWinningTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &AWinningTrigger::OnOverlap);
}

void AWinningTrigger::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("You Won"));
	}
}