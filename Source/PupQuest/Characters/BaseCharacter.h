// Written by 3016

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UBoxComponent;

UCLASS()
class PUPQUEST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void HandleDeath();                                         

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth {100.0f};
	
public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCharacterDead = false;
};