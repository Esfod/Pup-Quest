// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDoorActor.generated.h"

class ATriggerVolume;

UCLASS()
class PUPQUEST_API ABaseDoorActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp { nullptr };

	UPROPERTY(EditAnywhere, Category= "Componets")
	AActor* TorchHolder { nullptr };
	
	
	/*
	UPROPERTY(EditAnywhere, Category= "Componets")
	ATriggerVolume* PressurePlate{ nullptr };
    */

protected:
	UPROPERTY(EditAnywhere,Category="Variables")
	float MoveLength{300.f};

	UPROPERTY(EditAnywhere,Category="Variables")
	float DoorOpenSpeed{5.f};
	
	UPROPERTY(EditAnywhere,Category="Variables")
	float DoorCloseSpeed{7.5f};
	
	float Current;
	float Initial;
	bool bOpenDoor;
	
	bool CheckTorchHolder();
	
	virtual void BeginPlay() override;
	
	virtual void OpenDoor(float DeltaTime);
	
public:
	ABaseDoorActor();
};
