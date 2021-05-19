// Written by 3016

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
	
	virtual void Attack();
	
	UPROPERTY(EditAnywhere)
		float Damage {50.f};

	TArray<AActor*> GetOverLappingActorsFromSphere();
	
	TArray<AEnemyNestActor*> GetEnemyNestActors() const;

	protected:
	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category= "Detection Variable")
	float SphereRadius {90.f};
	
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* IdleInsect;

	UPROPERTY(EditAnywhere,Category = "Nest", meta = (AllowPrivateAccess = "true"))
	TArray<AEnemyNestActor*> NestActors {nullptr};
};