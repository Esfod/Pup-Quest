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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkRange{ 5000.f };
	
	AMainCharacter* MainCharacter { nullptr };
	
	void MoveAndRotateTowardsPlayer();

	float RetrunDistanceToPlayer();

	
public:
	AEnemyBaseCharacter();
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
};
