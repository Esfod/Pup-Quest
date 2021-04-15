// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderCharacter.h"

ASpiderCharacter::ASpiderCharacter()
{
}

void ASpiderCharacter::Tick(float DeltaSeconds)
{
	if(KnockOutTime != 0)
	{
		bIsEnemyKnockedOut = true;
		if(Timer + KnockOutTime == DeltaSeconds)
		{
			bIsEnemyKnockedOut = false;
			KnockOutTime = 0;
			Timer = 0.f; 
		}
	}
}
void ASpiderCharacter::Attack(float OwnerDamage)
{
	Super::Attack(OwnerDamage);
}

void ASpiderCharacter::GetHit(int32 ObjectInHand)
{
	Super::GetHit(ObjectInHand);
	switch (ObjectInHand)
	{
		case 0:
			KnockOutTime = 1;
			UE_LOG(LogTemp,Warning,TEXT("Spider is hit by hand"));
			break;
		case 1:
			KnockOutTime = 5;
			UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an unlit torch"));
			break;
		case 2:
			KnockOutTime = 5;
			UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an lit torch"));
			break;
		case 3:
			KnockOutTime = 7;
			UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an plank"));
			break;
		default:
			break;
	}
	Timer = GetWorld()->DeltaTimeSeconds;
}