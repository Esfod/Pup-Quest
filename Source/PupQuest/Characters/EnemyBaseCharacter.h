// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyBaseCharacter.generated.h"

class AMainCharacter;

UCLASS()
class PUPQUEST_API AEnemyBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private:
	AMainCharacter* MainCharacter{ nullptr };
	
public:
	AEnemyBaseCharacter();

	virtual void Tick(float DeltaTime) override;

	void Attack();
protected:

	virtual void BeginPlay() override;
	
};