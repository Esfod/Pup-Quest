// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderCharacter.h"

ASpiderCharacter::ASpiderCharacter()
{
}

void ASpiderCharacter::Tick(float DeltaSeconds)
{
	if(KnockOutTime != 0)
	{
		if(Timer == 0.0f)
			Timer = GetWorld()->GetRealTimeSeconds();
		bIsEnemyKnockedOut = true;
		if(Timer + KnockOutTime == GetWorld()->GetRealTimeSeconds())
		{
			bIsEnemyKnockedOut = false;
			KnockOutTime = 0;
			Timer = 0.0f; 
		}
	}
	//UE_LOG(LogTemp,Warning,TEXT("Timer = %f"), Timer);
	//UE_LOG(LogTemp,Warning,TEXT("KnockOutTime = %f"), KnockOutTime);
	//UE_LOG(LogTemp,Warning,TEXT("DeltaSeconds = %f"), DeltaSeconds);
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
			KnockOutTime = MeleeKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by hand"));
			break;
		case 1:
			KnockOutTime = TorchKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an unlit torch"));
			break;
		case 2:
			KnockOutTime = TorchKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an lit torch"));
			break;
		case 3:
			KnockOutTime = PlankKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an plank"));
			break;
		default:
			break;
	}
}