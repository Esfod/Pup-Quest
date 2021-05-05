// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderCharacter.h"

#include "GameFramework/PawnMovementComponent.h"
#include "PupQuest/Actors/BrazierActor.h"

ASpiderCharacter::ASpiderCharacter()
{
	//HitBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("AttackSocket"));
}

void ASpiderCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(!ComplexSpider)
	{
		RunDirecton = GetActorLocation() + RunToLocation;
		RunDirecton.Normalize();
	}
}

void ASpiderCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(ComplexSpider)
	{
		if(KnockOutTime > 0)
		{
			if(Timer == 0.0f)
				Timer = GetWorld()->GetTimeSeconds();
			bIsEnemyKnockedOut = true;
			if(Timer + KnockOutTime <= GetWorld()->GetTimeSeconds())
			{
				bIsEnemyKnockedOut = false;
				KnockOutTime = 0;
				Timer = 0.0f; 
			}
		}
		/*
		UE_LOG(LogTemp,Warning,TEXT("Timer = %f"), Timer);
		UE_LOG(LogTemp,Warning,TEXT("KnockOutTime = %f"), KnockOutTime);
		UE_LOG(LogTemp,Warning,TEXT("TimeSeconds DeltaSeconds = %f"), GetWorld()->GetTimeSeconds());
	
		if(bIsEnemyKnockedOut)
		{
		UE_LOG(LogTemp,Warning,TEXT("bIsEnemyKnockedOut = true"));
		}
		else
		{
		UE_LOG(LogTemp,Warning,TEXT("bIsEnemyKnockedOut = false"));
		}
		*/
	}
	else
	{
		if(BrazierActor!=nullptr && BrazierActor->bBrazierLit)
		{
			Run();
		}
	}
}

void ASpiderCharacter::Run()
{
	AddMovementInput(RunDirecton, 1);
	SetActorRotation(RunDirecton.Rotation());
}

void ASpiderCharacter::Attack(float OwnerDamage)
{
	Super::Attack(OwnerDamage);
}

void ASpiderCharacter::SpiderGettingHit(int32 ObjectInHand)
{
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
		case 4:
			KnockOutTime = BucketKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an Bucket"));
			break;
		default:
			break;
	}
}