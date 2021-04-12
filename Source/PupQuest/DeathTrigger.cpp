// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathTrigger.h"
#include "Characters/MainCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

ADeathTrigger::ADeathTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ADeathTrigger::OnOverlap);
	
}

void ADeathTrigger::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {

	if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		Main->HandleDeath();
		//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}