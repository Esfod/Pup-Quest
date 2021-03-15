// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PupQuest/ActorComponent/LineTrace.h"
#include "PupQuest/Actors/SpiderWebActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Actors/TorchHolderActor.h"
//#include "EnemyBaseCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Net/UnrealNetwork.h"

AMainCharacter::AMainCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f); // ...at this rotation rate

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp  = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArm);

	LineTraceComp = CreateDefaultSubobject<ULineTrace>(TEXT("LineTraceComponent"));
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
//	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
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

void AMainCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainCharacter, Item);
	/*DOREPLIFETIME(AAttachableWall, Weapon);*/
}

void AMainCharacter::Onrep_ItemAttachToHand()
{
	if (Item) 
	{
		Item->SetActorEnableCollision(false);
		Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("MainSocket"));
	}
}


void AMainCharacter::Interact() 
{
	FVector Start = GetMesh()->GetBoneLocation(FName("joint2"));
	FVector End = Start + this->GetActorRotation().Vector() * 150.0f;
	AActor* Actor = LineTraceComp->LineTraceSingle(Start, End, true);

	if (Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor is %s"), *Actor->GetName());
		if (holdingItem == false) {
			if (ATorchActor* TorchHit = Cast<ATorchActor>(Actor)) {
				Item = TorchHit;
				holdingItem = true;
				Onrep_ItemAttachToHand();
				UE_LOG(LogTemp, Warning, TEXT("Weapon picked up"));
			}
		}
		else {
		/*	if (AMyDoor* Door = Cast<AMyDoor>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Open door"));
			}*/
			if (ASpiderWebActor* Web = Cast<ASpiderWebActor>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Burn web"));
				Web->Destroy();
			}
			if (ATorchHolderActor* TorchHolder = Cast<ATorchHolderActor>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Place Torch"));

			}

			/*if (AAttachableWall* Wall = Cast<AAttachableWall>(Actor)) {
				UE_LOG(LogTemp, Warning, TEXT("Attach torch to wall"));
				Onrep_WeaponAttachToWall();
			}*/
		}
	}
}

AActor* AMainCharacter::CheckHitBoxPickUp()
{
	TArray<AActor*> OverlappingActors;
	//HitBox->GetOverlappingActors(OverlappingActors);
	for(AActor* Actor : OverlappingActors)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"), *Actor->GetName());

		if(Actor->IsA(ATorchActor::StaticClass()))
		{
			return Actor;
		}
	}
	
	return nullptr;
}

AActor* CheckHitBoxPlacment()
{
	/*TArray<AActor*> OverlappingActors;
	
	if(HitBox)
	{
		HitBox->GetOverlappingActors(OverlappingActors);
		for(AActor* Actor : OverlappingActors)
		{
			UE_LOG(LogTemp,Warning,TEXT("%s"), *Actor->GetName());

			if(Actor->IsA(ATorchActor::StaticClass()))
			{
				return Actor;
			}
		}
	}*/
		return nullptr;
}

AActor* CheckHitBoxAttack()
{
	/*TArray<AActor*> OverlappingActors;
	
	if(HitBox)
	{
		HitBox->GetOverlappingActors(OverlappingActors);
		for(AActor* Actor : OverlappingActors)
		{
			UE_LOG(LogTemp,Warning,TEXT("%s"), *Actor->GetName());

			if(Actor->IsA(AEnemyBaseCharacter::StaticClass()))
			{
				return Actor;
			}
		}
	}*/
	return nullptr;
}