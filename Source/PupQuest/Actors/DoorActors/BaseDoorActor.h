// Written by 3016

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

	//private functions
	bool CheckTorchHolder(ATorchHolderActor* a);
	
	bool CheckTorchHolder(ATorchHolderActor* a, ATorchHolderActor* b);
	
	bool CheckPressurePlate(APressurePlate_Actor* a);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "TorchHolder")
	ATorchHolderActor* TorchHolder1 { nullptr };

	UPROPERTY(EditAnywhere, Category = "TorchHolder")
	ATorchHolderActor* TorchHolder2 { nullptr };

	UPROPERTY(EditAnywhere, Category = "TorchHolder")
	APressurePlate_Actor* PressurePlate_Actor { nullptr };
	
	UPROPERTY(EditAnywhere, Category = "Variables")
	float TotalMoveLength{90.f}; //the length the door moves/rotate

	UPROPERTY(EditAnywhere, Category="Variables")
	float DoorOpenSpeed{5.f}; //
	
	UPROPERTY(EditAnywhere, Category="Variables")
	float DoorCloseSpeed{7.5f};

	float Current;
	
	float Initial;

	bool CloseDoorOverride {false};

	bool bOpenDoor;
	
	UPROPERTY(EditAnywhere,Category="Variables")
	bool IsDoorOpen {false};
	
	int32 TypeOfDoor { 0 };

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
