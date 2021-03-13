// Copyright Epic Games, Inc. All Rights Reserved.

#include "PickUpTestCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "LineTrace.h"
#include "Components/InputComponent.h"
#include "Public/WeaponBase.h"
#include "Public/MyDoor.h"
#include "Public/SpiderWeb.h"
#include "Public/AttachableWall.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// APickUpTestCharacter

APickUpTestCharacter::APickUpTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	LineTraceComp = CreateDefaultSubobject<ULineTrace>("LineTraceComponent");
}

void APickUpTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APickUpTestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APickUpTestCharacter::MoveRight);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APickUpTestCharacter::Interact);
	PlayerInputComponent->BindAction("Iteract", IE_Pressed, this, &APickUpTestCharacter::Onrep_WeaponAttachToHand);
}

void APickUpTestCharacter::BeginPlay() {
	Super::BeginPlay();

	//FActorSpawnParameters SpawnParams;
	//SpawnParams.bNoFail = true;
	//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	//if (WeaponClass) {

	//	FTransform WeaponTransform;
	//	WeaponTransform.SetLocation(FVector::ZeroVector);
	//	WeaponTransform.SetRotation(FQuat(FRotator::ZeroRotator));

	//	Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, WeaponTransform, SpawnParams);
	//	/*if (Weapon) {
	//		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RHand"));
	//	}*/
	//}
}

void APickUpTestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APickUpTestCharacter, Weapon);
	/*DOREPLIFETIME(AAttachableWall, Weapon);*/
}


void APickUpTestCharacter::Onrep_WeaponAttachToHand()
{
	if (Weapon) {
		Weapon->SetActorEnableCollision(false);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RHand"));
	}
}

//void AAttachableWall::OnRep_WeaponAttachToWall() {
//		holdingItem = false;
//		Weapon->SetActorEnableCollision(false);
//		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("TorchHolder"));
//}

void APickUpTestCharacter::MoveForward(float Value)
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

void APickUpTestCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
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

void APickUpTestCharacter::Interact() {
	FVector Start = GetMesh()->GetBoneLocation(FName("head"));
	FVector End = Start + this->GetActorRotation().Vector() * 150.0f;
	AActor* Actor = LineTraceComp->LineTraceSingle(Start, End, true);

	if (Actor) {
		UE_LOG(LogTemp, Warning, TEXT("Actor is %s"), *Actor->GetName());
		if (holdingItem == false) {
			if (AWeaponBase* HitWeapon = Cast<AWeaponBase>(Actor)) {
				Weapon = HitWeapon;
				holdingItem = true;
				Onrep_WeaponAttachToHand();
				UE_LOG(LogTemp, Warning, TEXT("Weapon picked up"));
			}
		}
		else {
			if (AMyDoor* Door = Cast<AMyDoor>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Open door"));
			}
			if (ASpiderWeb* Web = Cast<ASpiderWeb>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Burn web"));
				Web->Destroy();
			}
			/*if (AAttachableWall* Wall = Cast<AAttachableWall>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Attach torch to wall"));
				Onrep_WeaponAttachToWall();
			}*/
		}
	}
}