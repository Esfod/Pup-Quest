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
protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* HitBox { nullptr };
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void HandleDeath();

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth {100.0f};

	UPROPERTY(VisibleAnywhere)
	float Health {0.f}; 

	void IsCharacterDead();
public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCharacterDead = false;
};
