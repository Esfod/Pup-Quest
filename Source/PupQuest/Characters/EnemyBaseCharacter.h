// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyBaseCharacter.generated.h"

class AMainCharacter;
class AEnemyNestActor;

UCLASS()
class PUPQUEST_API AEnemyBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyBaseCharacter(); 

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category= "Detection Variable")
	float SphereRadius {90.f};
	
public:
	virtual void Attack(float OwnerDamage);
	
	UPROPERTY(EditAnywhere)
	float Damage {50.f};

	TArray<AActor*> GetOverLappingActorsFromSphere() const;

	UPROPERTY(BlueprintReadOnly)
	bool bIsAttacking {false};
	
	virtual void GetHit(int32 ObjectInHand);

	float KnockOutTime {0.f};
	
	TArray<AEnemyNestActor*> GetEnemyNestActors() const;
private:
	
	UPROPERTY(EditAnywhere)
	float AttackDistance{100.f};

	UPROPERTY(EditAnywhere,Category = "Nest")
	TArray<AEnemyNestActor*> NestActors {nullptr};
};