// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BarrelActor.generated.h"

UCLASS()
class PUPQUEST_API ABarrelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrelActor();


	//UFUNCTION(BlueprintCallable)
	//	void FindClosestPush();
	//
	//UFUNCTION(BlueprintCallable)
	//	void HandleInteraction();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Bools")
	bool bBarrelFilled;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Water;

	UFUNCTION()
		void BarrelFill();

	UFUNCTION()
		void BarrelEmpty();

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* FillBarrel;

	//UFUNCTION(BlueprintCallable)
	//void CheckIfOnPressurePlate();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
