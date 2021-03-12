// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDoorActor.generated.h"

UCLASS()
class PUPQUEST_API ABaseDoorActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComp {nullptr};

	UPROPERTY(EditAnywhere, Category= "Components")
	AActor* TorchHolderActor {nullptr};
	
protected:


	UPROPERTY(EditAnywhere,Category="Variables")
	float DoorOpenSpeed{5.f};
	
	UPROPERTY(EditAnywhere,Category="Variables")
	float DoorCloseSpeed{7.5f};
	
	float Current;
	float Initial;
	bool bOpenDoor;
	
	virtual void BeginPlay() override;
	bool CheckTorchHolder();
	
	virtual void OpenDoor(float DeltaTime);
	
public:
	ABaseDoorActor();
	
	virtual void Tick(float DeltaTime) override;

};
