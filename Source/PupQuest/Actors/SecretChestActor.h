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

	//virtual void OpenChest(float DeltaTime) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		UStaticMeshComponent* GetChestTopMesh();

};
