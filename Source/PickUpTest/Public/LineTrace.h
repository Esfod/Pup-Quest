// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineTrace.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PICKUPTEST_API ULineTrace : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULineTrace();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	AActor* LineTraceSingle(FVector Start, FVector End);
	AActor* LineTraceSingle(FVector Start, FVector End, bool ShowDebugLine);
};
