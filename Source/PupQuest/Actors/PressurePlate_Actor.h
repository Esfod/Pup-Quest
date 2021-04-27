// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate_Actor.generated.h"

class ABarrelActor;
UCLASS()
class PUPQUEST_API APressurePlate_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate_Actor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABarrelActor* GetBarrelActor() const;

	void PlaceBarrelRight(ABarrelActor* a);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	ABarrelActor* BarrelActor {nullptr};

};
