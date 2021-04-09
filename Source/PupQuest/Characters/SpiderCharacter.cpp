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
		if(Timer == 0.f)
			Timer = DeltaSeconds;
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
	UE_LOG(LogTemp,Error,TEXT("Getting hit"));
	switch (ObjectInHand)
	{
		case 0:
		KnockOutTime = 1;
		break;
		case 1:
		KnockOutTime = 5;
		break;
		case 2:
		KnockOutTime = 5;
		break;
		case 3:
		KnockOutTime = 7;
		break;
		default:
		break;
	}
}

void ASpiderCharacter::MoveForward(FVector WalkDirection, float ValueDirection)
{
	AddMovementInput(WalkDirection,ValueDirection);
}