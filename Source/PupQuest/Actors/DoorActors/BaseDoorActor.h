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

	UPROPERTY(EditAnywhere, Category= "Variables")
	bool bTorchHolder { true };
	

protected:
	UPROPERTY(EditAnywhere, Category = "Componets")
	const AActor* TorchHolder1 { nullptr };

	UPROPERTY(EditAnywhere, Category = "Componets")
	const AActor* TorchHolder2 { nullptr };
	
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

	bool CheckTorchHolder(const AActor* a);
	bool CheckTorchHolder(const AActor* a, const AActor* b);
	
	virtual void OpenDoor(float DeltaTime);
	
public:
	ABaseDoorActor();
	
	virtual void Tick(float DeltaTime) override;

};
