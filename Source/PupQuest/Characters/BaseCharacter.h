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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* HitBox {nullptr};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ABaseCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
