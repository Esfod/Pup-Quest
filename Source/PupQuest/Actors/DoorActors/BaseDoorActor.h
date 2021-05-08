// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "BaseDoorActor.generated.h"

class ATriggerVolume;
class ATorchHolderActor;
class APressurePlate_Actor;
UCLASS()
class PUPQUEST_API ABaseDoorActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp { nullptr };

	UPROPERTY(EditAnywhere, Category= "Variables",meta = (AllowPrivateAccess = "true"))
	bool bTorchHolder { true }; 

	bool CheckTorchHolder(ATorchHolderActor* a);
	bool CheckTorchHolder(ATorchHolderActor* a, ATorchHolderActor* b);
	bool CheckPressurePlate(APressurePlate_Actor* a);

	
protected:
	UPROPERTY(EditAnywhere, Category = "TorchHolder")
	ATorchHolderActor* TorchHolder1 { nullptr };

	UPROPERTY(EditAnywhere, Category = "TorchHolder")
	ATorchHolderActor* TorchHolder2 { nullptr };

	UPROPERTY(EditAnywhere, Category = "TorchHolder")
	APressurePlate_Actor* PressurePlate_Actor { nullptr };
	
	UPROPERTY(EditAnywhere,Category = "Variables")
	float TotalMoveLength{90.f};

	UPROPERTY(EditAnywhere,Category="Variables")
	float DoorOpenSpeed{5.f};
	
	UPROPERTY(EditAnywhere,Category="Variables")
	float DoorCloseSpeed{7.5f};

	float Current;
	float Initial;
	
	UPROPERTY(EditAnywhere,Category="Variables")
	bool IsDoorOpen {false};

	bool CloseDoorOverride {false};

	bool bOpenDoor;
	int32 TypeOfDoor { 0 };

	virtual void BeginPlay() override;
	
	virtual void OpenDoor(float DeltaTime);

	UPROPERTY(EditAnywhere, Category="Sound")
		USoundBase* OpenDoorSound {nullptr};
	UPROPERTY(EditAnywhere, Category="Sound")
		USoundBase* CloseDoorSound {nullptr};
	public:
	ABaseDoorActor();
	
	virtual void Tick(float DeltaTime) override;

	void CloseDoor();	
};
