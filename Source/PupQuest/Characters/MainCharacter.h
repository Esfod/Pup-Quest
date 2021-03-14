// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;

UCLASS()
class PUPQUEST_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent { nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* PlayerCameraComponent { nullptr };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* HitBox {nullptr};

public:
	AMainCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE  USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE  UCameraComponent* GetPlayerCameraComponent() const { return PlayerCameraComponent; }


protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Interact();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//class ULineTrace* LineTraceComp;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATorchActor> TorchClass;

	bool holdingItem = false;

	UPROPERTY(ReplicatedUsing = OnRep_ItemAttachToHand)
		class ATorchActor* Item;

	UFUNCTION()
		void Onrep_ItemAttachToHand();

	virtual void BeginPlay() override;

	// APawn interface
	// End of APawn interface

};
