// Fill out your copyright notice in the Description page of Project Settings.



#include "EnemyBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"


AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	FireBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box to check for closest fire"));
	FireBox->SetupAttachment(GetMesh());
	FireBox->SetGenerateOverlapEvents(true);
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
}

void AEnemyBaseCharacter::Attack(float OwnerDamage)
{
	//UE_LOG(LogTemp,Warning,TEXT("Start Attack"));
	TArray<AActor*> OverlappingActors;
	HitBox->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if(Actor->IsA(AMainCharacter::StaticClass()))
		{
			UE_LOG(LogTemp,Warning,TEXT("Spider treffer %s"), *Actor->GetName());
			AMainCharacter* MainCharacter = Cast<AMainCharacter>(Actor);
			if (MainCharacter == nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("MainCharacter fail"));
				return;
			}
		}
	}
}

TArray<AActor*> AEnemyBaseCharacter::GetOverLappingActorsToFireBox() const
{
	TArray<AActor*> OverlappingActors;
	FireBox->GetOverlappingActors(OverlappingActors);
	return OverlappingActors;
}

void AEnemyBaseCharacter::GetHit(int32 ObjectInHand)
{
	
}
