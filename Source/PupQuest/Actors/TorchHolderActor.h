// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorchHolderActor.generated.h"

UCLASS()
class PUPQUEST_API ATorchHolderActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* TorchPlacementPoint { nullptr };

protected:
	virtual void BeginPlay() override;

public:
	ATorchHolderActor();
	
	FTransform GetTorchPlacementPoint();
};