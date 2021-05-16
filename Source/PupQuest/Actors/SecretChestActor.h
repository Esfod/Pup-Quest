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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ChestBottom;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ChestTop;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 SecretsFound = 0;

	//virtual void OpenChest(float DeltaTime) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		UStaticMeshComponent* GetChestTopMesh();

	UPROPERTY(EditAnywhere, Category = "Name of secret")
		FName SecretName;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//int SecretsFound;

	UFUNCTION(BlueprintCallable)
		int GetChestActor();

	void OpenChest();

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* OpenSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* Angelic;

	bool bPotatoFound = false;

	bool bBeetrootFound = false;

	bool bCarrotFound = false;

	bool bOpened = false;

	//UFUNCTION(BlueprintCallable)
	//	int GetChestActor(int Secret);


	/*
	secrets = 3
	if openchest
		check which chest
		that chest secret = found
		secretsfoundcounter ++
	
	
	
	
	
	*/


};
