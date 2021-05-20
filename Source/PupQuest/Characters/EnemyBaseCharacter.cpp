// Written by 3016



#include "EnemyBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
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
	UGameplayStatics::PlaySoundAtLocation(this, IdleInsect, GetActorLocation() - SoundLocation);
}

void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
}

void AEnemyBaseCharacter::Attack()
{
	//UE_LOG(LogTemp,Warning,TEXT("%s is Attacking"), *GetName());
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;
	//DrawDebugBox(GetWorld(),GetActorLocation() + GetActorForwardVector()*100, FVector(50.f), FColor::Red, true,2);

	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), GetActorLocation() + GetActorForwardVector()*100, FVector(50.f), ObjectTypes, nullptr, ActorsToIgnore, OverlappedActors);
	//gets all actors in a box in front of enemy

	//UE_LOG(LogTemp,Warning,TEXT("%s attacks %s"),*GetName(), *OtherActor->GetName());
	for(AActor* Actor : OverlappedActors) //goes trough every overlapped actor
	{
		if(Actor->IsA(AMainCharacter::StaticClass())) //stops if it hits maincharcter
		{
			//UE_LOG(LogTemp,Warning,TEXT("Spider treffer "), *Actor->GetName());
			AMainCharacter* MainCharacter = Cast<AMainCharacter>(Actor);
			if (MainCharacter == nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("MainCharacter fail"));
				return;
			}
			UE_LOG(LogTemp,Warning,TEXT("Spider attacks Player"));
			MainCharacter->PlayerTakeDamage(Damage); //deal damage too player
		}
	}
}

TArray<AActor*> AEnemyBaseCharacter::GetOverLappingActorsFromSphere()
{
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	//ActorsToIgnore.Add(this);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Red, true,2);
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), SphereRadius, ObjectTypes,nullptr,ActorsToIgnore,OverlappedActors);
	//gets all actor from a larger radius around the enemy to check for fire

	/* 
	for(AActor* Actor : OverlappedActors)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s's Sphere overlaps with %s"),*GetName(), *Actor->GetName());
	}
	*/
	return OverlappedActors; //returns the overlapped actors
}

TArray<AEnemyNestActor*> AEnemyBaseCharacter::GetEnemyNestActors() const
{
	return NestActors; //retrun all nest actors
}