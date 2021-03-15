// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ULineTrace;
class ATorchActor;

UCLASS()
class PUPQUEST_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm { nullptr };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp { nullptr };


	AActor* CheckHitBoxPickUp();
	AActor* CheckHitBoxPlacment();
	AActor* CheckHitBoxAttack();
	//hello

	public:
	AMainCharacter();


	protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Interact();

	ULineTrace* LineTraceComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATorchActor> ItemClass;

	bool holdingItem = false;

	UPROPERTY(ReplicatedUsing = OnRep_ItemAttachToHand)
	ATorchActor* Item;

	UFUNCTION()
        void Onrep_ItemAttachToHand();

	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
};
