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

	virtual void Tick(float DeltaTime) override;

	virtual void Attack(float OwnerDamage);
	
	UPROPERTY(EditAnywhere)
	float Damage {50.f};

	TArray<AActor*> GetOverLappingActorsToFireBox();

	bool bIsEnemyKnockedOut = false;
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void GetHit(int32 ObjectInHand);

	UPROPERTY(BlueprintReadOnly)
	float KnockOutTime {0.f};
	
private:
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* FireBox { nullptr };
	
	UPROPERTY(EditAnywhere)
	float AttackDistance{100.f};

};