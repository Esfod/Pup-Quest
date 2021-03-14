// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
//#include "TorchActor.h"
#include "Net/UnrealNetwork.h"

AMainCharacter::AMainCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bInheritYaw = false;

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>("Player Camera Component");
	PlayerCameraComponent->SetupAttachment(SpringArmComponent);


	HitBox = CreateDefaultSubobject<UBoxComponent>("Player Hit Box");
	HitBox->SetupAttachment(RootComponent);
	HitBox->InitBoxExtent(FVector(50.f,50.f,50.f));
	HitBox->SetGenerateOverlapEvents(false);
//Fredirsh
//// Set size for collision capsule
//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
//LineTraceComp = CreateDefaultSubobject<ULineTrace>("LineTraceComponent");
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
//	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
//	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Onrep_WeaponAttachToHand);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Onrep_ItemAttachToHand);

}

void AMainCharacter::BeginPlay() {
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

void AMainCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	DOREPLIFETIME(AMainCharacter, Item);
//	/*DOREPLIFETIME(AAttachableWall, Weapon);*/
}

void AMainCharacter::Onrep_ItemAttachToHand()
{
//	if (Item) {
//		Item->SetActorEnableCollision(false);
//		Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("MainSocket"));
//	}
}

void AMainCharacter::Interact()
{
//	FVector Start = GetMesh()->GetBoneLocation(FName("joint2"));
//	FVector End = Start + this->GetActorRotation().Vector() * 150.0f;
//	AActor* Actor = LineTraceComp->LineTraceSingle(Start, End, true);
//
//	if (Actor) {
//		UE_LOG(LogTemp, Warning, TEXT("Actor is %s"), *Actor->GetName());
//		if (holdingItem == false) {
//			if (ATorchActor* TorchHit = Cast<ATorchActor>(Actor)) {
//				Item = TorchHit;
//				holdingItem = true;
//				Onrep_ItemAttachToHand();
//				UE_LOG(LogTemp, Warning, TEXT("Weapon picked up"));
//			}
//		}
//		/*else {
//			if (AMyDoor* Door = Cast<AMyDoor>(Actor)) {
//				UE_LOG(LogTemp, Warning, TEXT("Open door"));
//			}*/
//			/*if (ASpiderWeb* Web = Cast<ASpiderWeb>(Actor)) {
//				UE_LOG(LogTemp, Warning, TEXT("Burn web"));
//				Web->Destroy();
//			}*/
//			/*if (AAttachableWall* Wall = Cast<AAttachableWall>(Actor)) {
//				UE_LOG(LogTemp, Warning, TEXT("Attach torch to wall"));
//				Onrep_WeaponAttachToWall();
//			}
//		}*/
//	}

}