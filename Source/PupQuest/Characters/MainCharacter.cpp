// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PupQuest/Actors/SpiderWebActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Actors/ItemsActor/PlankActor.h"
#include "PupQuest/Actors/TorchHolderActor.h"
#include "PupQuest/Actors/BrazierActor.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMainCharacter::AMainCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(0.f, -30.f, 15.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritYaw = false;

	CameraComp  = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArm);

	HitBox->SetRelativeLocation(FVector(70.f,0.f, 0.f));

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlap);
	
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
//	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::StartInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::StopInteract);

	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropTorch);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropPlank);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(MoveForwardVector.X != 0 || MoveRightVector.Y != 0)
		RotatePlayerTowardsWalkDirection();
}

void AMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
	MoveForwardVector = GetActorForwardVector() * Value;
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
	MoveRightVector = GetActorRightVector() * Value;
}

void AMainCharacter::RotatePlayerTowardsWalkDirection()
{
	float InitialYaw = GetMesh()->GetRelativeRotation().Yaw;
    FVector MoveDirection = MoveForwardVector + MoveRightVector;
	float RotateToYaw = MoveDirection.Rotation().Yaw;
	float CurrentYaw = FMath::Lerp(InitialYaw, RotateToYaw, GetWorld()->DeltaTimeSeconds*RotateSpeed);
	
	GetMesh()->SetRelativeRotation(FRotator(0.f,CurrentYaw,0.f));
}

void AMainCharacter::TorchAttachToHand()
{
	if (Torch) 
	{
		Torch->SetActorEnableCollision(false);
		Torch->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("MainSocket"));
		bHoldingTorch = true;
		UE_LOG(LogTemp, Warning, TEXT("Torch picked up"));
		pickupItem = false;
	}
}

void AMainCharacter::PlankAttachToHand()
{
	if (Plank) {
		Plank->SetActorEnableCollision(false);
		Plank->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("plank socket"));
		bHoldingPlank = true;
		UE_LOG(LogTemp, Warning, TEXT("Plank picked up"));
		pickupItem = false;
	}
}

void AMainCharacter::DropTorch() {
	if (bHoldingTorch == true) {
		FVector Location = Torch->GetActorLocation() + FVector(100.f, 0.f, 0.f);
		Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Torch->SetActorEnableCollision(true);
		Torch->SetActorLocation(Location);
		bHoldingTorch = false;
		UE_LOG(LogTemp, Warning, TEXT("Torch dropped"));
	}
}

void AMainCharacter::DropPlank() {
	if (bHoldingPlank == true) {
		FVector Location = GetMesh()->GetComponentLocation() + FVector(100.f, 0.f, 0.f);
		Plank->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Plank->SetActorEnableCollision(true);
		Plank->SetActorLocation(Location);
		bHoldingPlank = false;
		UE_LOG(LogTemp, Warning, TEXT("Plank dropped"));
	}
}

void ATorchActor::StartTorchFlame() {
	UE_LOG(LogTemp, Warning, TEXT("Torch is now lit"));
}

void ABrazierActor::StartBrazierFlame() {
	UE_LOG(LogTemp, Warning, TEXT("Brazier is now lit"));
}

void AMainCharacter::StartInteract() {
	//UE_LOG(LogTemp, Warning, TEXT("Interact!"));
	HitBox->SetGenerateOverlapEvents(true);
	pickupItem = true;
}

void AMainCharacter::StopInteract() {
	//UE_LOG(LogTemp, Warning, TEXT("Stop Interact!"));
	HitBox->SetGenerateOverlapEvents(false);
}

void AMainCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	if (bHoldingTorch == false && bHoldingPlank == false) {
			if (OtherActor->IsA(ATorchActor::StaticClass()))
			{
				ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
				Torch = TorchHit;
				bTorchLit = Torch->bTorchLit;
				TorchAttachToHand();

				UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));

			}
			if (OtherActor->IsA(APlankActor::StaticClass()))
				{
				APlankActor* PlankHit = Cast<APlankActor>(OtherActor);
				Plank = PlankHit;
				PlankAttachToHand();			}
		}
	else if (bHoldingTorch == true) {
		if (OtherActor->IsA(ATorchHolderActor::StaticClass())) {
			if (bTorchLit == true) {
				ATorchHolderActor* TorchHolder = Cast<ATorchHolderActor>(OtherActor);
				Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				Torch->SetActorEnableCollision(true);
				Torch->SetActorLocation(TorchHolder->GetTorchPlacementPoint());
				bHoldingTorch = false;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Door will not open because the torch is not lit"));
			}
		}
		if (bTorchLit == true) {
				if (OtherActor->IsA(ASpiderWebActor::StaticClass())) {
					ASpiderWebActor* Web = Cast<ASpiderWebActor>(OtherActor);
					//Web->BurnWeb();
					UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
					//Web->HitBoxWeb->SetGenerateOverlapEvents(true);
				}
		}

		if (OtherActor->IsA(APlankActor::StaticClass()) && pickupItem == true)
		{
			DropTorch();
			APlankActor* PlankHit = Cast<APlankActor>(OtherActor);
			Plank = PlankHit;
			PlankAttachToHand();
		}

	}

	if (bHoldingPlank == true) {
		if (OtherActor->IsA(ATorchActor::StaticClass()) && pickupItem == true)
		{
			DropPlank();

			ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
			Torch = TorchHit;
			bTorchLit = Torch->bTorchLit;
			TorchAttachToHand();

			//UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));

		}
	}


	if (OtherActor->IsA(ABrazierActor::StaticClass())) {
		ABrazierActor* Brazier = Cast<ABrazierActor>(OtherActor);
		UBrazier = Brazier;
		bBrazierLit = UBrazier->bBrazierActorLit;
		UE_LOG(LogTemp, Warning, TEXT("Brazier lit is %s"), bBrazierLit ? TEXT("true") : TEXT("false"));
		UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));
		if (bHoldingTorch == true) {
			if (bBrazierLit == true) {
				if (bTorchLit == true) {
					UE_LOG(LogTemp, Warning, TEXT("Brazier and torch is already lit"));
				}
				else {
					bTorchLit = true;
					Torch->ATorchActor::StartTorchFlame();
				}
			}
			else {
				if (bTorchLit == true) {
					UBrazier->ABrazierActor::StartBrazierFlame();
					bBrazierLit = true;
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("Your Torch has to be lit to light the brazier"));
				}
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("You are not holding a torch"));
		}
	}
}