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
	CameraComp  = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArm);

	/*StandOnHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxWeb"));
	StandOnHitBox->SetupAttachment(RootComponent);*/
	/*StandOnHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::StandOnOverlapBegin);
	StandOnHitBox->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::StandOnOverlapEnd);*/

	HitBox->SetRelativeLocation(FVector(70.f,0.f, 0.f));
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlap);

	AttackBoxComponent = CreateDefaultSubobject<UBoxComponent>("Attack HitBox");
	AttackBoxComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Attack_Box_Attach"));

	MoveIgnoreActorAdd(Plank);
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
	
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropTorch);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropPlank);

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
}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator PlayerRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, PlayerRotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator PlayerRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, PlayerRotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::TorchAttachToHand()//F.M
{
	//if (OnTopOff == false) {
		if (Torch)
		{
			//Torch->MeshComp->SetSimulatePhysics(false);
			Torch->SetActorEnableCollision(false);//Skrur av collision på torch
			Torch->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("TorchSocket"));//Attach torch til main character
			bHoldingTorch = true;
			UE_LOG(LogTemp, Warning, TEXT("Torch picked up"));
			Interacting = false;//Passer på at du ikke kan plukke opp noe mer en en gang når du trykker på E, så etter torch er plukket opp kan man ikke plukke opp noe mer
		}
	//}
}

void AMainCharacter::PlankAttachToHand()//F.M
{
	//if (OnTopOff == false) {
		if (Plank) {
			Plank->SetActorEnableCollision(false);//Skrur av collision på plank
			Plank->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("PlankSocket"));//Attach plank til main character
			bHoldingPlank = true;
			UE_LOG(LogTemp, Warning, TEXT("Plank picked up"));
			Interacting = false;//Passer på at du ikke kan plukke opp noe mer en en gang når du trykker på E, så etter torch er plukket opp kan man ikke plukke opp noe mer
		}
	//}
}

void AMainCharacter::DropTorch()//F.M
{
	if (bHoldingTorch == true) {
		//Torch->MeshComp->SetSimulatePhysics(true);
		Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach torch fra main character
		Torch->SetActorEnableCollision(true);//Skrur på collision igjen

		FVector DropLocation = Torch->GetActorLocation() + FVector(0.f, 0.f, -40.f);//Bestemmer lokasjonen torch skal bli droppet
		Torch->SetActorRotation(FQuat(FRotator(-85.f, GetMesh()->GetRelativeRotation().Yaw -45.f, 0.f)));//Gir planke riktig rotasjon
		Torch->SetActorLocation(DropLocation);//Plasserer torchen på drop lokasjonen

		bHoldingTorch = false;
		Torch->TorchFlameOff();
		UE_LOG(LogTemp, Warning, TEXT("Torch dropped"));
	}
}

void AMainCharacter::DropPlank()//F.M
{
	if (bHoldingPlank == true) {
		Plank->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach planken fra main character
		Plank->SetActorEnableCollision(true);//Skrur på collision igjen

		Plank->SetActorRotation(FQuat(FRotator(0.f, GetMesh()->GetRelativeRotation().Yaw + 90.f, 270.f)));//Gir planke riktig rotasjon
		FVector DropLocation = Plank->GetActorLocation() + FVector(0.f, 0.f, -30.f);//Bestemmer lokasjonen planken skal bli droppet
		Plank->SetActorLocation(DropLocation);//Plasserer planken på drop lokasjonen

		bHoldingPlank = false;
		UE_LOG(LogTemp, Warning, TEXT("Plank dropped"));
	}
}

void AMainCharacter::PlacePlank()//F.M 
{
	if (bHoldingPlank == true && InTriggerBox == true) {



		Plank->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach planken fra main character
		Plank->SetActorEnableCollision(true);//Skrur på collision igjen

		Plank->SetActorLocation(Location);//Plasserer planken på drop lokasjonen FVector(10500.0f, 9480.0f, 500.0f)
		Plank->SetActorScale3D(FVector(13.f));//Gir planke riktig størrelse
		Plank->SetActorRelativeRotation(FQuat(Rotation));//Gir planke riktig rotasjon FRotator(-1.5f, 0.f, 90.f))

		bHoldingPlank = false;
		UE_LOG(LogTemp, Warning, TEXT("Plank placed"));
	}
}

void AMainCharacter::StartInteract() {//F.M
	//UE_LOG(LogTemp, Warning, TEXT("Interact!"));
	HitBox->SetGenerateOverlapEvents(true);//Skrur på hitboxen så den registrerer om noe er i den
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

	if (bHoldingTorch == false && bHoldingPlank == false) {//Hvis karakteren ikke holder torch eller planke
			if (OtherActor->IsA(ATorchActor::StaticClass()))//Hvis det er torch
			{
				ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
				Torch = TorchHit;
				bTorchLit = Torch->bTorchLit;
				TorchAttachToHand();

				UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchLit ? TEXT("true") : TEXT("false"));
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
			ATorchHolderActor* TorchHolder = Cast<ATorchHolderActor>(OtherActor);
			if (Torch->bTorchLit == true) {//Hvis torch er lit

				Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Karakteren slutter å holde torch
				Torch->SetActorEnableCollision(true);//Skrur på collision igjen
				Torch->SetActorLocation(TorchHolder->GetTorchPlacementPoint());//Setter torch i torch holder
				Torch->SetActorRotation(TorchHolder->GetTorchPlacementPoint().Rotation());
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

		if (OtherActor->IsA(APlankActor::StaticClass()) && Interacting == true)//Hvis det er planke
		{
			DropTorch();//Dropper torch
			APlankActor* PlankHit = Cast<APlankActor>(OtherActor);
			Plank = PlankHit;
			PlankAttachToHand();//Attach planke til karakter
		}

	}

	if (bHoldingPlank == true) {//Hvis karakteren holder planke
		if (OtherActor->IsA(ATorchActor::StaticClass()) && Interacting == true)//Hvis det er torch
		{
			DropPlank();//Dropp planke

			ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
			Torch = TorchHit;
			TorchAttachToHand();//Attach torch til karakter

			//UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), bTorchLit ? TEXT("true") : TEXT("false"));

		}
	}


	if (OtherActor->IsA(ABrazierActor::StaticClass())) {//Hvis det er brazier
		ABrazierActor* UBrazier = Cast<ABrazierActor>(OtherActor);
		Brazier = UBrazier;
		UE_LOG(LogTemp, Warning, TEXT("Brazier lit is %s"), Brazier->bBrazierLit ? TEXT("true") : TEXT("false"));
		UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchLit ? TEXT("true") : TEXT("false"));
		if (bHoldingTorch == true) {//Hvis karakter holder torch
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
		else {//Hvis karakteren ikke holder torch
			UE_LOG(LogTemp, Warning, TEXT("You are not holding a torch"));
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
	if(Torch != nullptr)
		return Torch;
	else
		return nullptr;
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