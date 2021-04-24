// Fill out your copyright notice in the Description page of Project Settings.



#include "EnemyBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

#include "MainCharacter.h"
#include "PupQuest/Actors/EnemyNestActor.h"

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
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
	//UE_LOG(LogTemp,Warning,TEXT("%s is Attacking"), *GetName());
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;
	//DrawDebugBox(GetWorld(),GetActorLocation() + GetActorForwardVector()*100, FVector(50.f), FColor::Red, true,2);
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), GetActorLocation() + GetActorForwardVector()*100, FVector(50.f), ObjectTypes, nullptr, ActorsToIgnore, OverlappedActors);
	//UE_LOG(LogTemp,Warning,TEXT("%s attacks %s"),*GetName(), *OtherActor->GetName());
	for(AActor* Actor : OverlappedActors)
	if(Actor->IsA(AMainCharacter::StaticClass()))
	{
		//UE_LOG(LogTemp,Warning,TEXT("Spider treffer "), *Actor->GetName());
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(Actor);
		if (MainCharacter == nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("MainCharacter fail"));
			return;
		}
		UE_LOG(LogTemp,Warning,TEXT("Spider attacks Player"));
		MainCharacter->PlayerTakeDamage(Damage);
	}
}

TArray<AActor*> AEnemyBaseCharacter::GetOverLappingActorsFromSphere() const
{
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	//ActorsToIgnore.Add(this);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Red, true,2);
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), SphereRadius, ObjectTypes,nullptr,ActorsToIgnore,OverlappedActors);

	for(AActor* Actor : OverlappedActors)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s's Sphere overlaps with %s"),*GetName(), *Actor->GetName());
	}
	return OverlappedActors;
}

TArray<AEnemyNestActor*> AEnemyBaseCharacter::GetEnemyNestActors() const
{
	return NestActors;
}