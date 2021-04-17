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
	
public:
	
	AEnemyBaseCharacter(); 

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void Attack(float OwnerDamage);
	
public:
	UPROPERTY(EditAnywhere)
	float Damage {50.f};

	TArray<AActor*> GetOverLappingActorsToFireBox() const;

	UPROPERTY(BlueprintReadOnly)
	bool bIsEnemyKnockedOut {false};

	UPROPERTY(BlueprintReadOnly)
	bool bIsAttacking {false};
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void GetHit(int32 ObjectInHand);

	float KnockOutTime {0.f};
	
private:
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* FireBox { nullptr };
	
	UPROPERTY(EditAnywhere)
	float AttackDistance{100.f};

};