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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkRange{ 2000.f };

	AMainCharacter* MainCharacter{ nullptr };

	float RetrunDistanceToMainCharacter();

	void WalkAndRotateTowardsMainCharacter();
	
public:
	AEnemyBaseCharacter();

	virtual void Tick(float DeltaTime) override;

	protected:

	virtual void BeginPlay() override;
	
};