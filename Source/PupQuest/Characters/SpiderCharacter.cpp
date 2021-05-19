// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderCharacter.h"
#include "PupQuest/Actors/BrazierActor.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ASpiderCharacter::ASpiderCharacter()
{
	//HitBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("AttackSocket"));
}

void ASpiderCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(!ComplexSpider) //checks if this spider does not use the AIController
	{
		RunDirecton = RunToLocation-GetActorLocation(); //calculates the direction to the location
		RunDirecton.Normalize(); //normalize the vector to make it the distance of 1
	}
}

void ASpiderCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(ComplexSpider)
	{
		if(KnockOutTime > 0) // checks if the knockout time is more than 0, this gets set in SpiderGettingHit()
		{
			if(Timer == 0.0f)
			{
				Timer = GetWorld()->GetTimeSeconds(); //saves the time the knockout happened
                bIsEnemyKnockedOut = true; //start the knockout
			}
		
			if(bIsEnemyKnockedOut && Timer + KnockOutTime <= GetWorld()->GetTimeSeconds()) //if the timer + the knockouttime is less or equal to world time
			{
				bIsEnemyKnockedOut = false; //makes the spider able to move again
				KnockOutTime = 0.f; 
				Timer = 0.0f;
				//resets values
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
		if(BrazierActor!=nullptr && BrazierActor->bBrazierLit) //checks that the brazier it's connected to is lit
		{
			Run(); //makes it run to location
		}
	}
}

void ASpiderCharacter::Run()
{
	SetActorLocation(GetActorLocation() + RunDirecton * 600 * GetWorld()->DeltaTimeSeconds); //makes spider run too location
	SetActorRotation(RunDirecton.Rotation()); //makes it look at location it runes too
	//DrawDebugLine(GetWorld(),GetActorLocation(),RunToLocation,FColor::Blue,false,2,1,3);
	if(GetActorLocation().Y > RunToLocation.Y) Destroy(); //when it comes too location it destroy it self
}

void ASpiderCharacter::Attack()
{
	Super::Attack(); //calls super
}

void ASpiderCharacter::SpiderGettingHit(int32 ObjectInHand)
{
	UGameplayStatics::PlaySoundAtLocation(this, TakingDamage, GetActorLocation()); // play hit taking damage sound
	switch (ObjectInHand) //checks if what kind of object the spider is getting hit with
	{
		case 0: //hit by fist
			KnockOutTime = MeleeKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by hand"));
			break;
		case 1: //hit by unlit torch
			KnockOutTime = TorchKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an unlit torch"));
			break;
		case 2: //hit by lit torch
			KnockOutTime = TorchKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an lit torch"));
			break;
		case 3: //hit by plank
			KnockOutTime = PlankKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an plank"));
			break;
		case 4: //hit by bucket
			KnockOutTime = BucketKnockOutTime;
			//UE_LOG(LogTemp,Warning,TEXT("Spider is hit by an Bucket"));
			break;
		default:
			break;
	}
}