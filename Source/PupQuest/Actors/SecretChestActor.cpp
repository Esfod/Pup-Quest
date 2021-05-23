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

UStaticMeshComponent* ASecretChestActor::GetChestTopMesh() {
	return ChestTop;
}


void ASecretChestActor::OpenChest() {
	if (bOpened == false) {
		GetChestTopMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -50.f));
		UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
		GameInstance->SecretsFound++;
		UE_LOG(LogTemp, Warning, TEXT("Secrets found: %d"), GameInstance->SecretsFound);

		UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, Angelic, GetActorLocation());
	}
}

