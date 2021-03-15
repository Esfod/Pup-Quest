// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

AEnemyBaseCharacter::EnemyBaseCharacter()
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
	if (MainCharacter && RetrunDistanceToMainCharacter() < WalkRange)
	{
		WalkAndRotateTowardsMainCharacter();
	}
}
void AEnemyBaseCharacter::WalkAndRotateTowardsMainCharacter()
{
	FVector VectorTowardsPlayer = MainCharacter->GetActorLocation() - GetActorLocation();
	FRotator RotationTowardsPlayer = VectorTowardsPlayer.Rotation;
	
	SetActorRotation(VectorTowardsPlayer);
	AddMovementInput(Direction, Value);
}

float AEnemyBaseCharacter::RetrunDistanceToMainCharacter()
{
	return FVector::Dist(MainCharacter->GetActorLocation(), GetActorLocation());
}