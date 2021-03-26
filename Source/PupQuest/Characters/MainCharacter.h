// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ATorchActor;
class ABrazierActor;

UCLASS()
class PUPQUEST_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm { nullptr };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp { nullptr };

	FVector MoveForwardVector;
	FVector MoveRightVector;

	UPROPERTY(EditAnywhere)
	float RotateSpeed = 30.f;
public:
	AMainCharacter();

	void DropItem();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void RotatePlayerTowardsWalkDirection();
	
	void StartInteract();
	void StopInteract();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATorchActor> ItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool HoldingTorch = false;

	UPROPERTY()
	ATorchActor* Item;
	bool bTorchLit;

	UPROPERTY()
	ABrazierActor* UBrazier;

	bool bBrazierLit;

	UFUNCTION()
        void ItemAttachToHand();



	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	bool Interacting = false;


	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
};
