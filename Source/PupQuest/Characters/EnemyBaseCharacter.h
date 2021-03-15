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
	float WalkRange{ 2000.f };

	AMainCharacter* MainCharacter;
};
