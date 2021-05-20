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
class ABarrelActor;
class UPupQuestGameInstance;
class UAudioComponent;
UCLASS()
class PUPQUEST_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	//components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm { nullptr };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp { nullptr };

	UPROPERTY(VisibleAnywhere, Category = "BoxComponents", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackBoxComponent {nullptr};

	UPROPERTY(EditAnywhere, Category = "BoxComponents", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* HitBox { nullptr };

	AActor* DroppedItem = nullptr;//This is used to see what the latest dropped item was

	UPROPERTY(EditAnywhere)
	float RotateSpeed = 30.f;
	//funtions
	void AttackStart();

	void AttackEnd();

	void UnlimtedHealth();
	
	void RegainHealth(float DeltaTime);

	//sounds
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* MusicLevel1;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* MusicLevel2;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* PlaceItem;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* NolanBarking;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* AmbienceSound;
	
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* PickUpItem;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* AttackTorch;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* LightBrazier;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* TakingDamage;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* AntTakingDamage;

		USoundBase* PushingBarrelSoundBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
		UAudioComponent* PushingBarrelSound;

		USoundBase* MenuMusicBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
		UAudioComponent* MenuMusic;

		USoundBase* IntroSoundBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
		UAudioComponent* IntroSound;

		USoundBase* CutsceneSoundBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
		UAudioComponent* CutsceneSound;

public:
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Health {0.f};

	float RegainHealthTimer{0.f};
	
	bool InPlankTriggerBox = false;

	bool OnTopOff = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bTorchLit {false};//See if the torch is lit or not
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bPushingBarrel = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bHoldingTorch = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bHoldingPlank = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bHoldingBucket = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bIsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bPushBool = false;

	UPROPERTY(VisibleAnywhere, Category = "Variables")
	int Pushing = 1;

	FRotator DropRotation;//Used to set the dropping rotation of dropped items

	FVector ItemLocationAdjustment;//Small adjustments for each dropped item, so they get the right location
	
	FVector PlacePlankLocation;

	FRotator PlacePlankRotation;

	UFUNCTION(BlueprintCallable)
	virtual void HandleDeath() override;

	UFUNCTION()
	void PlacePlank();

	void IsCharacterDead();

	UFUNCTION(BlueprintCallable)
	void IsPushing();

	UFUNCTION(BlueprintCallable)
	void StopMenuMusic();
	
	UFUNCTION()
	void AttachItem(AActor* Item);

	UFUNCTION()
    void DropHoldingItem();

	UFUNCTION()
    void DropItem(AActor* Item);

	void PlayerTakeDamage(float DamageTaken);

	UFUNCTION(BlueprintCallable)
	ATorchActor* GetTorchActor();

	UFUNCTION(BlueprintCallable)
	ABucketActor* GetBucketActor();

	UFUNCTION(BlueprintCallable)
	UPupQuestGameInstance* GetChestActor();

	FName ItemSocket;

	protected:
	
	APlankActor* Plank;

	ATorchActor* Torch;

	ABarrelActor* Barrel;

	ABucketActor* Bucket;

	ABrazierActor* Brazier;

	AWellActor* Well;

	UPROPERTY(EditAnywhere,Category="HealthRegain")
	float TimeToRegain{5.f};
	
	UPROPERTY(EditAnywhere,Category="HealthRegain")
	float AmountOfHealthRegain {20.f};

	UPROPERTY(EditAnywhere, Category="Speed")
	float NormalWalkMaxSpeed{400.f};
	
	UPROPERTY(EditAnywhere, Category="Speed")
	float HoldingPlankSpeed{150.f};

	bool bBrazierLit;

	bool Interacting = false;//So you don't pick up something you just dropped
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);
	
	void StartInteract();
	
	void StopInteract();

	

	UFUNCTION()
		void OnOverlapHitBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnOverlapAttackBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
};