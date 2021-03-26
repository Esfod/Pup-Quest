// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PupQuest/Actors/SpiderWebActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Actors/TorchHolderActor.h"
#include "PupQuest/Actors/BrazierActor.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMainCharacter::AMainCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f); // ...at this rotation rate

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(0.f, -30.f, 15.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritYaw = false;

	CameraComp  = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArm);

	HitBox->SetRelativeLocation(FVector(70.f,0.f, 0.f));

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlap);
	//HitBox->SetGenerateOverlapEvents(true);
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
//	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::StartInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::StopInteract);

	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropItem);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::ItemAttachToHand()
{
	if (Item) 
	{
		Item->SetActorEnableCollision(false);
		Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("MainSocket"));
		HoldingTorch = true;
		UE_LOG(LogTemp, Warning, TEXT("Item picked up"));
	}
}

void AMainCharacter::DropItem() {
	FVector Location = GetOwner()->GetActorLocation();
	Item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Item->SetActorEnableCollision(true);
	Item->SetActorLocation(Location);
	HoldingTorch = false;
}

void ATorchActor::StartTorchFlame() {
	UE_LOG(LogTemp, Warning, TEXT("Torch is now lit"));
}

void ABrazierActor::StartBrazierFlame() {
	UE_LOG(LogTemp, Warning, TEXT("Brazier is now lit"));
}

void AMainCharacter::StartInteract() {
	UE_LOG(LogTemp, Warning, TEXT("Interact!"));
	HitBox->SetGenerateOverlapEvents(true);
}

void AMainCharacter::StopInteract() {
	UE_LOG(LogTemp, Warning, TEXT("Stop Interact!"));
	HitBox->SetGenerateOverlapEvents(false);
}

void AMainCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
		
	if (HoldingTorch == false) {
			if (OtherActor->IsA(ATorchActor::StaticClass()))
			{
				ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
				Item = TorchHit;
				bTorchLit = Item->bTorchLit;

				UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));

				ItemAttachToHand();

				
			}
		}
	else {
		if (OtherActor->IsA(ATorchHolderActor::StaticClass())) {
			if (bTorchLit == true) {
				ATorchHolderActor* TorchHolder = Cast<ATorchHolderActor>(OtherActor);
				Item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				Item->SetActorEnableCollision(true);
				Item->SetActorLocation(TorchHolder->GetTorchPlacementPoint());
				HoldingTorch = false;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Door will not open because the torch is not lit"));
			}
		}
		if (bTorchLit == true) {
				if (OtherActor->IsA(ASpiderWebActor::StaticClass())) {
					ASpiderWebActor* Web = Cast<ASpiderWebActor>(OtherActor);
					UE_LOG(LogTemp, Warning, TEXT("Burn web"));
					Web->SetActorHiddenInGame(true);
					Web->SetActorEnableCollision(false);
					//functon(Web);
				}
			}
	}

	if (OtherActor->IsA(ABrazierActor::StaticClass())) {
		ABrazierActor* Brazier = Cast<ABrazierActor>(OtherActor);
		UBrazier = Brazier;
		bBrazierLit = UBrazier->bBrazierActorLit;
		UE_LOG(LogTemp, Warning, TEXT("Brazier lit is %s"), bBrazierLit ? TEXT("true") : TEXT("false"));
		UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));
		if (HoldingTorch == true) {
			if (bBrazierLit == true) {
				if (bTorchLit == true) {
					UE_LOG(LogTemp, Warning, TEXT("Brazier and torch is already lit"));
				}
				else {
					bTorchLit = true;
					Item->ATorchActor::StartTorchFlame();
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