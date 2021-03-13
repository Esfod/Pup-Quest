// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttachableWall.generated.h"

UCLASS()
class PICKUPTEST_API AAttachableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttachableWall();

	//UPROPERTY(ReplicatedUsing = OnRep_WeaponAttachToWall)
	//	class AWeaponBase* Weapon;

	//UFUNCTION()
	//	void Onrep_WeaponAttachToWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
