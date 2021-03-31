// Fill out your copyright notice in the Description page of Project Settings.



#include "EnemyBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}