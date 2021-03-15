// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));	
}

void AEnemyBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(RetrunDistanceToPlayer() < WalkRange)
	{
		MoveAndRotateTowardsPlayer();
	}
}

void AEnemyBaseCharacter::MoveAndRotateTowardsPlayer()
{
	FVector MoveDirection = MainCharacter->GetActorLocation() - GetActorLocation();
	SetActorRotation(MoveDirection.Rotation());
	AddMovementInput(MoveDirection, 1);
}

float AEnemyBaseCharacter::RetrunDistanceToPlayer()
{
	if (!MainCharacter)
	{ return 0.f; }
	return FVector::Dist(MainCharacter->GetActorLocation(), GetActorLocation());
}


