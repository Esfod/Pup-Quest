// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include "BucketActor.generated.h"


UCLASS()
class PUPQUEST_API ABucketActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:
	ABucketActor();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Bools")
		bool bBucketFilled;

	UFUNCTION()
		void BucketFill();

	UFUNCTION()
		void BucketEmpty();

private:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Water;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* FillBucket;


	virtual void BeginPlay() override;
};
