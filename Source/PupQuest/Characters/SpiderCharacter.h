// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseCharacter.h"
#include "SpiderCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API ASpiderCharacter : public AEnemyBaseCharacter
{
	GENERATED_BODY()
public:
	ASpiderCharacter();

	virtual void Attack(float OwnerDamage) override;

	virtual void GetHit(int32 ObjectInHand) override;

	UPROPERTY(EditAnywhere, Category = "Values")
	float RotationSpeed {150};

protected:

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "KnockOut Times")
	float MeleeKnockOutTime {1.f};
	
	UPROPERTY(EditAnywhere, Category = "KnockOut Times")
	float TorchKnockOutTime {1.f};
	
	UPROPERTY(EditAnywhere, Category = "KnockOut Times")
	float PlankKnockOutTime {1.f};
	
private:
	float Timer {0.f}; 
};
