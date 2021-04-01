// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrazierActor.generated.h"

UCLASS()
class PUPQUEST_API ABrazierActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrazierActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bBrazierActorLit = false;

	UFUNCTION()
		void StartBrazierFlame();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;
};
