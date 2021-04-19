// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Barrel_ActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUPQUEST_API UBarrel_ActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBarrel_ActorComponent();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variables")
		float PushSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variables")
		float PushRange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
