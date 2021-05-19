// Written by 3016

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorchHolderActor.generated.h"

class ATorchActor;
UCLASS()
class PUPQUEST_API ATorchHolderActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* TorchPlacementPoint { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Components", meta =(AllowPrivateAccess = "true"))
	ATorchActor* TorchActor {nullptr};


protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHasATorch {false};

public:
	ATorchHolderActor(); 

	ATorchActor* GetTorchActor() const;

	bool HasATorch() const;
	
	void SetTorchActor(ATorchActor* TorchActor);
	
	FTransform GetTorchPlacementPoint() const;
};