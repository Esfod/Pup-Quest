// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDoorActor.generated.h"

class ATriggerVolume;
class ATorchHolderActor;
UCLASS()
class PUPQUEST_API ABaseDoorActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp { nullptr };

	UPROPERTY(EditAnywhere, Category= "Variables")
	bool bTorchHolder { true };

	bool CheckTorchHolder(ATorchHolderActor* a);
	bool CheckTorchHolder(ATorchHolderActor* a, ATorchHolderActor* b);

protected:
	UPROPERTY(EditAnywhere, Category = "TorchHolder")
	ATorchHolderActor* TorchHolder1 { nullptr };

	UPROPERTY(EditAnywhere, Category = "TorchHolder")
	ATorchHolderActor* TorchHolder2 { nullptr };
	
	UPROPERTY(EditAnywhere,Category="Variables")
	float MoveLength{300.f};

	UPROPERTY(EditAnywhere,Category="Variables")
	float DoorOpenSpeed{5.f};
	
	UPROPERTY(EditAnywhere,Category="Variables")
	float DoorCloseSpeed{7.5f};
	
	float Current;
	float Initial;
	bool bOpenDoor;

	int32 TypeOfDoor { 0 };

	virtual void BeginPlay() override;
	
	virtual void OpenDoor(float DeltaTime);
	
public:
	ABaseDoorActor();
	
	virtual void Tick(float DeltaTime) override;

};
