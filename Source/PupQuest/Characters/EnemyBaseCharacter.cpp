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
	HitBox->SetGenerateOverlapEvents(true);

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
	for (AActor* Actors : OverlappingActors)
	{
		if(Actors->IsA(AMainCharacter::StaticClass()))
		{
			FHitResult Hit;
			AController* OwnerController = this->GetController();
			AMainCharacter* MainCharacter = Cast<AMainCharacter>(Actors);
			if (OwnerController == nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("OwnerController fail"));
				return;
			}
			if (MainCharacter == nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("MainCharacter fail"));
				return;
			}
			if (this == nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("this fail"));
				return;
			}
			
			bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, this->GetActorForwardVector(), this->GetActorForwardVector()*10, ECollisionChannel::ECC_GameTraceChannel1);
			if (bSuccess)
			{
				FVector HitDirection = MainCharacter->GetActorLocation() - this->GetActorLocation();
                FPointDamageEvent DamageEvent(OwnerDamage, Hit, HitDirection, nullptr);
                MainCharacter->TakeDamage(OwnerDamage, DamageEvent, OwnerController, this);
			}
		}
	}
}

TArray<AActor*> AEnemyBaseCharacter::GetOverLappingActorsToFireBox()
{
	TArray<AActor*> OverlappingActors;
	FireBox->GetOverlappingActors(OverlappingActors);
	return OverlappingActors;
}