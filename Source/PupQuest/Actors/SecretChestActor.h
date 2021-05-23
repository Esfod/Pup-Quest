// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecretChestActor.generated.h"

UCLASS()
class PUPQUEST_API ASecretChestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecretChestActor();


protected:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ChestBottom;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ChestTop;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 SecretsFound = 0;

public:	

	UFUNCTION()
		UStaticMeshComponent* GetChestTopMesh();

	UPROPERTY(EditAnywhere, Category = "Name of secret")
		FName SecretName;

	void OpenChest();

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* OpenSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* Angelic;

	bool bOpened = false;
};
