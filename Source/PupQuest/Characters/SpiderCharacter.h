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

	virtual void Attack() override;

	virtual void SpiderGettingHit(int32 ObjectInHand) ;

	UPROPERTY(BlueprintReadOnly)
	bool bIsEnemyKnockedOut {false};
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "KnockOut Times")
	float MeleeKnockOutTime {1.f};
	
	UPROPERTY(EditAnywhere, Category = "KnockOut Times")
	float TorchKnockOutTime {5.f};
	
	UPROPERTY(EditAnywhere, Category = "KnockOut Times")
	float PlankKnockOutTime {7.f};

	UPROPERTY(EditAnywhere, Category = "KnockOut Times")
	float BucketKnockOutTime {3.f};

	UPROPERTY(EditAnywhere,Category="Run")
	bool ComplexSpider{true};

	UPROPERTY(EditAnywhere,Category="Run")
	class ABrazierActor* BrazierActor {nullptr};

	UPROPERTY(EditAnywhere,Category="Run")
	FVector RunToLocation {0.f};

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* TakingDamage;
private:
	float Timer {0.f};

	float KnockOutTime {0.f};

	void Run();

	FVector RunDirecton{0.f};
};
