// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseCharacter.h"
#include "AntCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API AAntCharacter : public AEnemyBaseCharacter
{
	GENERATED_BODY()

	public:
	AAntCharacter();

	void AntGettingHit();

	virtual void Attack() override;

	protected:
	virtual void Tick(float DeltaSeconds) override;
};
