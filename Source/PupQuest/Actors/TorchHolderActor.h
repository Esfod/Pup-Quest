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

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Bool", meta =(AllowPrivateAccess = "true"))
	bool bHasATorch {false};

	public:
	
	ATorchHolderActor(); 

	ATorchActor* GetTorchActor() const;
	
	void SetTorchActor(ATorchActor* TorchActor);
	
	bool HasATorch() const;
	
	FTransform GetTorchPlacementPoint() const;
};