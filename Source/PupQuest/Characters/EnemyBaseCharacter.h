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
	UPROPERTY(EditAnywhere)
	UBoxComponent* FireBox { nullptr };
	
	UPROPERTY(EditAnywhere)
	float AttackDistance{100.f};

public:
	AEnemyBaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void Attack(float OwnerDamage);
	
	UPROPERTY(EditAnywhere)
	float Damage {50.f};

	TArray<AActor*> GetOverLappingActorsToFireBox();
	
protected:
	virtual void BeginPlay() override;

};