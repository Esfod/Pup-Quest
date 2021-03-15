// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UBoxComponent;

UCLASS()
class PUPQUEST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
private:




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UBoxComponent* HitBox{ nullptr };

public:
	ABaseCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
