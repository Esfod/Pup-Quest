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

//#include "PupQuest/Hud/P_Torch"

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

	//Flame->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Test burning"));
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::StartInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::StopInteract);

	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropTorch);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropPlank);

	PlayerInputComponent->BindAction("Place", IE_Pressed, this, &AMainCharacter::PlacePlank);
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

void AMainCharacter::TorchAttachToHand()//F.M
{
	if (Torch) 
	{
		Torch->SetActorEnableCollision(false);//Skrur av collision på torch
		Torch->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("TorchSocket"));//Attach torch til main character
		bHoldingTorch = true;
		UE_LOG(LogTemp, Warning, TEXT("Torch picked up"));
		pickupItem = false;//Passer på at du ikke kan plukke opp noe mer en en gang når du trykker på E, så etter torch er plukket opp kan man ikke plukke opp noe mer
	}
}

void AMainCharacter::PlankAttachToHand()//F.M
{
	if (Plank) {
		Plank->SetActorEnableCollision(false);//Skrur av collision på plank
		Plank->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("PlankSocket"));//Attach plank til main character
		bHoldingPlank = true;
		UE_LOG(LogTemp, Warning, TEXT("Plank picked up"));
		pickupItem = false;//Passer på at du ikke kan plukke opp noe mer en en gang når du trykker på E, så etter torch er plukket opp kan man ikke plukke opp noe mer
	}
}

void AMainCharacter::DropTorch()//F.M
{
	if (bHoldingTorch == true) {
		FVector DropLocation = Torch->GetActorLocation() + FVector(100.f, 0.f, 0.f);//Bestemmer lokasjonen torch skal bli droppet
		Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach torch fra main character
		Torch->SetActorEnableCollision(true);//Skrur på collision igjen
		Torch->SetActorLocation(DropLocation);//Plasserer torchen på drop lokasjonen
		bHoldingTorch = false;
		UE_LOG(LogTemp, Warning, TEXT("Torch dropped"));
	}
}

void AMainCharacter::DropPlank()//F.M
{
	if (bHoldingPlank == true) {
		FVector DropLocation = GetMesh()->GetComponentLocation() + FVector(100.f, 0.f, 0.f);//Bestemmer lokasjonen planken skal bli droppet
		Plank->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach planken fra main character
		Plank->SetActorEnableCollision(true);//Skrur på collision igjen
		Plank->SetActorLocation(DropLocation);//Plasserer planken på drop lokasjonen

		bHoldingPlank = false;
		UE_LOG(LogTemp, Warning, TEXT("Plank dropped"));
	}
}

void AMainCharacter::PlacePlank()//F.M 
{
	if (bHoldingPlank == true && InTriggerBox == true) {
		FVector PlaceLocation = FVector(10310.0f, 9430.0f, 500.0f);
		Plank->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach planken fra main character
		Plank->SetActorEnableCollision(true);//Skrur på collision igjen
		Plank->SetActorLocation(PlaceLocation);//Plasserer planken på drop lokasjonen
		Plank->SetActorScale3D(FVector( 0.25, 0.25, 0.25));//Gir planke riktig størrelse
		Plank->SetActorRotation(FQuat(FRotator(270.f, 0.f, 0.f)));//Gir planke riktig rotasjon
		Plank->SetActorRotation(FQuat(FRotator(0.f, 90.f, -90.f)));//Gir planke riktig rotasjon

		bHoldingPlank = false;
		UE_LOG(LogTemp, Warning, TEXT("Plank placed"));
	}
}

void ATorchActor::StartTorchFlame() {
	UE_LOG(LogTemp, Warning, TEXT("Torch is now lit"));
}

void ABrazierActor::StartBrazierFlame() {
	UE_LOG(LogTemp, Warning, TEXT("Brazier is now lit"));
}

void AMainCharacter::StartInteract() {//F.M
	//UE_LOG(LogTemp, Warning, TEXT("Interact!"));
	HitBox->SetGenerateOverlapEvents(true);//Skrur på hitboxen så den registrerer om noe er i den
	pickupItem = true;
}

void AMainCharacter::StopInteract()//F.M
{
	//UE_LOG(LogTemp, Warning, TEXT("Stop Interact!"));
	HitBox->SetGenerateOverlapEvents(false);//Skrur av hitboxen igjen
}

void AMainCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) //F.M
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	if (bHoldingTorch == false && bHoldingPlank == false) {//Hvis karakteren ikke holder torch eller planke
			if (OtherActor->IsA(ATorchActor::StaticClass()))//Hvis det er torch
			{
				ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
				Torch = TorchHit;
				bTorchLit = Torch->bTorchLit;
				TorchAttachToHand();

				UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));

			}
			if (OtherActor->IsA(APlankActor::StaticClass()))//Hvis det er planke
				{
				APlankActor* PlankHit = Cast<APlankActor>(OtherActor);
				Plank = PlankHit;
				PlankAttachToHand();			
			}
	}
	else if (bHoldingTorch == true) {//Hvis karakteren holder torch
		if (OtherActor->IsA(ATorchHolderActor::StaticClass())) {//Hvis det er en torch holder
			if (bTorchLit == true) {//Hvis torch er lit
				ATorchHolderActor* TorchHolder = Cast<ATorchHolderActor>(OtherActor);

				Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Karakteren slutter å holde torch
				Torch->SetActorEnableCollision(true);//Skrur på collision igjen
				Torch->SetActorLocation(TorchHolder->GetTorchPlacementPoint());//Setter torch i torch holder
				bHoldingTorch = false;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Door will not open because the torch is not lit"));
			}
		}
		if (bTorchLit == true) {//Hvis torch er lit
				if (OtherActor->IsA(ASpiderWebActor::StaticClass())) {//Hvis det er spider web
					ASpiderWebActor* Web = Cast<ASpiderWebActor>(OtherActor);
					//Web->BurnWeb();
					//UE_LOG(LogTemp, Warning, TEXT("player detects %s"), *OtherActor->GetName());
					Web->HitBoxWeb->SetGenerateOverlapEvents(true);
					//Web->BurnWeb();
				}
		}

		if (OtherActor->IsA(APlankActor::StaticClass()) && pickupItem == true)//Hvis det er planke
		{
			DropTorch();//Dropper torch
			APlankActor* PlankHit = Cast<APlankActor>(OtherActor);
			Plank = PlankHit;
			PlankAttachToHand();//Attach planke til karakter
		}

	}

	if (bHoldingPlank == true) {//Hvis karakteren holder planke
		if (OtherActor->IsA(ATorchActor::StaticClass()) && pickupItem == true)//Hvis det er torch
		{
			DropPlank();//Dropp planke

			ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
			Torch = TorchHit;
			bTorchLit = Torch->bTorchLit;
			TorchAttachToHand();//Attach torch til karakter

			//UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));

		}
	}


	if (OtherActor->IsA(ABrazierActor::StaticClass())) {//Hvis det er brazier
		ABrazierActor* Brazier = Cast<ABrazierActor>(OtherActor);
		UBrazier = Brazier;
		bBrazierLit = UBrazier->bBrazierActorLit;
		UE_LOG(LogTemp, Warning, TEXT("Brazier lit is %s"), bBrazierLit ? TEXT("true") : TEXT("false"));
		UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));
		if (bHoldingTorch == true) {//Hvis karakter holder torch
			if (bBrazierLit == true) {//Hvis brazier er lit
				if (bTorchLit == true) {//Hvis torch er lit
					UE_LOG(LogTemp, Warning, TEXT("Brazier and torch is already lit"));
				}
				else {//Hvis ikke er torch lit
					bTorchLit = true;
					Torch->ATorchActor::StartTorchFlame();
				}
			}
			else {//Hvis ikke er brazier lit
				if (bTorchLit == true) {//Hvis torch er lit
					UBrazier->ABrazierActor::StartBrazierFlame();
					bBrazierLit = true;
				}
				else {//Hvis torch ikke er lit
					UE_LOG(LogTemp, Warning, TEXT("Your Torch has to be lit to light the brazier"));
				}
			}
		}
		else {//Hvis karakteren ikke holder torch
			UE_LOG(LogTemp, Warning, TEXT("You are not holding a torch"));
		}
	}
}

void AMainCharacter::HandleDeath()
{
	Super::HandleDeath();

}