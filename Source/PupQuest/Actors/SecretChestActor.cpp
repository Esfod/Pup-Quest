// Fill out your copyright notice in the Description page of Project Settings.


#include "SecretChestActor.h"
#include "Kismet/GameplayStatics.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "PupQuest/PupQuestGameInstance.h"

// Sets default values
ASecretChestActor::ASecretChestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestBottom = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = ChestBottom;

	ChestTop = CreateDefaultSubobject<UStaticMeshComponent>("PointLight");
	ChestTop->SetupAttachment(ChestBottom);
}

// Called when the game starts or when spawned
void ASecretChestActor::BeginPlay()
{
	Super::BeginPlay();

	//OpenChest(DeltaTime);
}

// Called every frame
void ASecretChestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* ASecretChestActor::GetChestTopMesh() {
	return ChestTop;
}

//void ASecretChestActor::OpenChest(float DeltaTime) {
//	//Current = FMath::Lerp(0.f, MoveLength, DeltaTime * DoorOpenSpeed); //Open Door
//}

void ASecretChestActor::OpenChest() {
	if (bOpened == false) {
		GetChestTopMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -50.f));
		UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
		GameInstance->SecretsFound++;
		SecretsFound++;
		UE_LOG(LogTemp, Warning, TEXT("Secrets found: %d"), GameInstance->SecretsFound);

		UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, Angelic, GetActorLocation());


		if (SecretName == TEXT("Potato")) {
			UE_LOG(LogTemp, Warning, TEXT("You found Elinors Potato!"));
			bPotatoFound = true;
		}
		else if (SecretName == TEXT("Beetroot")) {
			UE_LOG(LogTemp, Warning, TEXT("You found the Beetroot!"));
			bBeetrootFound = true;
		}
		else if (SecretName == TEXT("Carrot")) {
			UE_LOG(LogTemp, Warning, TEXT("You found the Carrot!"));
			bCarrotFound = true;
		}
		bOpened = true;
	}
}


int ASecretChestActor::GetChestActor()
{
	int Secret = SecretsFound;
	//UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
	//int Secret = GameInstance->SecretsFound;
	return Secret;
}

