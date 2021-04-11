// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

#include "DrawDebugHelpers.h"

#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PupQuest/Actors/SpiderWebActor.h"
#include "PupQuest/PlacePlankTrigger.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Actors/ItemsActor/PlankActor.h"
#include "PupQuest/Actors/TorchHolderActor.h"
#include "PupQuest/Actors/BrazierActor.h"


#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

#include "PupQuest/Characters/SpiderCharacter.h"

//#include "PupQuest/Hud/P_Torch"



AMainCharacter::AMainCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(0.f, -30.f, 15.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritYaw = false;
	this->
	CameraComp  = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArm);

	/*StandOnHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxWeb"));
	StandOnHitBox->SetupAttachment(RootComponent);*/


	HitBox->SetRelativeLocation(FVector(70.f,0.f, 0.f));

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlap);

	/*StandOnHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::StandOnOverlapBegin);
	StandOnHitBox->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::StandOnOverlapEnd);*/

	//MoveIgnoreActorAdd(Plank);

}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::StartInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::StopInteract);

	PlayerInputComponent->BindAction("Attack",IE_Pressed,this, &AMainCharacter::Attack);
	
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropHoldingItem);
	PlayerInputComponent->BindAction("Place", IE_Pressed, this, &AMainCharacter::PlacePlank);

	PlayerInputComponent->BindAction("Reset", IE_Pressed, this, &AMainCharacter::HandleDeath);
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

void AMainCharacter::AttachItem(AActor* Item) {
		Interacting = false;//Passer p� at du ikke kan plukke opp noe mer en en gang n�r du trykker p� E, s� etter torch er plukket opp kan man ikke plukke opp noe mer
		DropHoldingItem();

		Item->SetActorEnableCollision(false);//Skrur av collision

		if (Item == Torch) {
			Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("TorchSocket"));//Attach torch til main character
			bHoldingTorch = true;
			UE_LOG(LogTemp, Warning, TEXT("Torch picked up"));
		}

		if (Item == Plank) {
			Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("PlankSocket"));//Attach plank til main character
			bHoldingPlank = true;
			UE_LOG(LogTemp, Warning, TEXT("Plank picked up"));
		}
}

void AMainCharacter::DropHoldingItem()//F.M
{
	if (bHoldingPlank == true) {
		DropItem(Plank);
	}
	if (bHoldingTorch == true) {
		DropItem(Torch);
	}
}

void AMainCharacter::DropItem(AActor* Item)//F.M
{
	if (Item) {
		Item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach torch fra main character
		Item->SetActorEnableCollision(true);//Skrur p� collision igjen

		FVector CharacterLocation = GetMesh()->GetComponentLocation() - FVector(0.f, 0.f, 10.f);
		FVector DropLocation = CharacterLocation + (GetMesh()->GetForwardVector() * 60.f);

		if (Item == Plank) {
			DropRotation = FRotator(0.f, GetMesh()->GetRelativeRotation().Yaw + 90.f, 270.f);
			bHoldingPlank = false;
			UE_LOG(LogTemp, Warning, TEXT("Plank dropped"));
		}

		if (Item == Torch) {
			DropRotation = FRotator(-85.f, GetMesh()->GetRelativeRotation().Yaw - 45.f, 0.f);
			bHoldingTorch = false;
			Torch->TorchFlameOff();
			UE_LOG(LogTemp, Warning, TEXT("Torch dropped"));
		}

		Item->SetActorRotation(FQuat(DropRotation));
		Item->SetActorLocation(DropLocation);
	}
}

void AMainCharacter::PlacePlank()//F.M 
{
	if (bHoldingPlank == true && InTriggerBox == true) {

		Plank->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach planken fra main character
		Plank->SetActorEnableCollision(true);//Skrur p� collision igjen

		Plank->SetActorLocation(Location);//Plasserer planken p� drop lokasjonen
		Plank->SetActorScale3D(FVector(13.f));//Gir planke riktig st�rrelse
		Plank->SetActorRelativeRotation(FQuat(Rotation));//Gir planke riktig rotasjon

		bHoldingPlank = false;
		UE_LOG(LogTemp, Warning, TEXT("Plank placed"));
	}
}

void AMainCharacter::StartInteract() {//F.M
	//UE_LOG(LogTemp, Warning, TEXT("Interact!"));
	HitBox->SetGenerateOverlapEvents(true);//Skrur p� hitboxen s� den registrerer om noe er i den
	Interacting = true;
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
	if (OtherActor->IsA(ATorchActor::StaticClass()) && Interacting == true)//Hvis det er torch
	{
		ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
		Torch = TorchHit;
		AttachItem(Torch);
		UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchLit ? TEXT("true") : TEXT("false"));
	}
	if (OtherActor->IsA(APlankActor::StaticClass()) && Interacting == true)//Hvis det er planke
	{
		APlankActor* PlankHit = Cast<APlankActor>(OtherActor);
		Plank = PlankHit;
		AttachItem(Plank);
	}
	else if (bHoldingTorch == true) {//Hvis karakteren holder torch
		if (OtherActor->IsA(ATorchHolderActor::StaticClass())) {//Hvis det er en torch holder
			ATorchHolderActor* TorchHolder = Cast<ATorchHolderActor>(OtherActor);
			if (Torch->bTorchLit == true) {//Hvis torch er lit
				Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Karakteren slutter � holde torch
				Torch->SetActorEnableCollision(true);//Skrur p� collision igjen
				Torch->SetActorLocation(TorchHolder->GetTorchPlacementPoint());//Setter torch i torch holder
				bHoldingTorch = false;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Door will not open because the torch is not lit"));
			}
		}
		if (Torch->bTorchLit == true) {//Hvis torch er lit
			if (OtherActor->IsA(ASpiderWebActor::StaticClass())) {//Hvis det er spider web
				ASpiderWebActor* Web = Cast<ASpiderWebActor>(OtherActor);
				//UE_LOG(LogTemp, Warning, TEXT("player detects %s"), *OtherActor->GetName());
				if (Web->bBurning == false) {
					Web->StartBurnWeb();
				}
			}
		}
		if (OtherActor->IsA(ABrazierActor::StaticClass())) {//Hvis det er brazier
			ABrazierActor* UBrazier = Cast<ABrazierActor>(OtherActor);
			Brazier = UBrazier;
			UE_LOG(LogTemp, Warning, TEXT("Brazier lit is %s"), Brazier->bBrazierLit ? TEXT("true") : TEXT("false"));
			UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchLit ? TEXT("true") : TEXT("false"));
			if (Brazier->bBrazierLit == true) {//Hvis brazier er lit
				if (Torch->bTorchLit == true) {//Hvis torch er lit
					UE_LOG(LogTemp, Warning, TEXT("Brazier and torch is already lit"));
				}
				else {//Hvis torch ikke er lit
				Torch->TorchFlameOn();
				}
			}
			else {//Hvis brazier ikke er lit
				if (Torch->bTorchLit == true) {//Hvis torch er lit
					Brazier->BrazierFlameOn();
				}
				else {//Hvis torch ikke er lit
					UE_LOG(LogTemp, Warning, TEXT("Your Torch has to be lit to light the brazier"));
				}
			}
		}
	}
}


void AMainCharacter::StandOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) //F.M
{
	//if (OtherActor->IsA(ATorchActor::StaticClass()) || OtherActor->IsA(APlankActor::StaticClass()))//Hvis det er torch
	//{
	//	OnTopOff = true;
	//}
}

void AMainCharacter::StandOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) //F.M
{
	//if (OtherActor->IsA(ATorchActor::StaticClass()) || OtherActor->IsA(APlankActor::StaticClass()))//Hvis det er torch
	//{
	//	OnTopOff = false;
	//}
}

void AMainCharacter::HandleDeath()
{
	//Super::HandleDeath();
	//GetWorld()->GetTimerManager().SetTimer(TimeGone, this, &AMainCharacter::Test, 5.f, false);
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	//if (CheckpointLocation == true) {
		//UE_LOG(LogTemp, Warning, TEXT("Hello there"));
		//SetActorLocation(FVector(7000.f,9500.f,580.f));
	//}
}


ATorchActor* AMainCharacter::GetTorchActor()
{
	return Torch;
}

void AMainCharacter::Attack()
{
	UE_LOG(LogTemp,Warning,TEXT("Attack"));
	//DrawDebugBox(GetWorld(), GetActorLocation()+GetMesh()->GetForwardVector()*25,FVector(25,25,50), FColor::Purple, true, -1, 0, 10);
	HitBox->SetGenerateOverlapEvents(true);
	TArray<AActor*> OverlappingActors;
	HitBox->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		UE_LOG(LogTemp,Error,TEXT("Actor hit %s"), *Actor->GetName());
		if(Actor->IsA(ASpiderCharacter::StaticClass()))
		{
			ASpiderCharacter* SpiderHit = Cast<ASpiderCharacter>(Actor);
			if(bHoldingTorch)
			{
				if(bTorchLit)
					SpiderHit->GetHit(2);
				else
					SpiderHit->GetHit(1);
			}
			else if(bHoldingPlank)
				SpiderHit->GetHit(3);
			else
				SpiderHit->GetHit(0);
		}
	}
	HitBox->SetGenerateOverlapEvents(false);
}