// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ATorchActor;
class APlacePlankTrigger;
class APlankActor;
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

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* AttackBoxComponent {nullptr};

	FVector MoveForwardVector;
	FVector MoveRightVector;

	UPROPERTY(EditAnywhere)
	float RotateSpeed = 30.f;

	void Attack();
public:
	AMainCharacter();

	UFUNCTION()
	void AttachItem(AActor* Item);

	UFUNCTION()
		void DropHoldingItem();

	UFUNCTION()
	void DropItem(AActor* Item);

	FRotator DropRotation;


	void PlacePlank();

	bool InTriggerBox = false;

	UPROPERTY(EditAnywhere)
		UBoxComponent* StandOnHitBox { nullptr };//To see if player is standing on item when he picks it up(movement does not work if he does)

	bool OnTopOff = false;


	ATorchActor* GetTorchActor();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bHoldingTorch = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bHoldingPlank = false;
	
	bool bTorchLit;

	AActor* DroppedItem = nullptr;

	FVector Location;

	FRotator Rotation;

	virtual void HandleDeath() override;

	//FVector NewLocation = FVector(50.f,50.f,50.f);

	bool CheckpointLocation = false;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);
	
	void StartInteract();
	
	void StopInteract();

	UPROPERTY()
		APlankActor* Plank;

	UPROPERTY()
		ATorchActor* Torch;

	UPROPERTY()
		ABrazierActor* Brazier;

	bool bBrazierLit;


	bool Interacting = false;//So you don't pick up something you just dropped

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void StandOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void StandOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
};
