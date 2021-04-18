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
class ABucketActor;
class AWellActor;

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

	UPROPERTY(EditAnywhere)
	float RotateSpeed = 30.f;

	void AttackStart();

	void AttackEnd();

	AActor* DroppedItem = nullptr;
public:
	AMainCharacter();

	UPROPERTY(EditAnywhere)
	UBoxComponent* StandOnHitBox { nullptr };//To see if player is standing on item when he picks it up(movement does not work if he does)

	FRotator DropRotation;

	ATorchActor* GetTorchActor();

	bool bTorchLit {false};

	bool bBucketFilled{ false };
	
	bool InTriggerBox = false;

	bool OnTopOff = false;
	
	bool CheckpointLocation = false; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bHoldingTorch = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bHoldingPlank = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
		bool bHoldingBucket = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bIsAttacking = false;

	FVector Location;

	FRotator Rotation;

	virtual void HandleDeath() override;

	void PlacePlank();
	
	UFUNCTION()
	void AttachItem(AActor* Item);

	UFUNCTION()
    void DropHoldingItem();

	UFUNCTION()
    void DropItem(AActor* Item);

	void PlayerTakeDamage(float DamageTaken);
	
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
		ABucketActor* Bucket;

	UPROPERTY()
		ABrazierActor* Brazier;

	UPROPERTY()
		AWellActor* Well;

	bool bBrazierLit;

	bool Interacting = false;//So you don't pick up something you just dropped

	UFUNCTION()
		void OnOverlapHitBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void StandOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapAttackBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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