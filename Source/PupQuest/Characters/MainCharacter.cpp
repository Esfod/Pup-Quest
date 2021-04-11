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
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapHitBox);

	AttackBoxComponent = CreateDefaultSubobject<UBoxComponent>("Attack HitBox");
	//AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Attack_Box_Attach")); //TODO Add when attack-animation is implemented
	AttackBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapAttackBox);
	
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

	PlayerInputComponent->BindAction("Attack",IE_Pressed,this, &AMainCharacter::AttackStart);
	PlayerInputComponent->BindAction("Attack",IE_Released,this, &AMainCharacter::AttackEnd);
	
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
	if(DroppedItem)
	{
		//UE_LOG(LogTemp,Warning,TEXT("DroppedItem name %s"),*DroppedItem->GetName());
		DroppedItem = nullptr;
	}
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
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::AttachItem(AActor* Item) {
		//Interacting = false;//Passer på at du ikke kan plukke opp noe mer en en gang når du trykker på E, så etter torch er plukket opp kan man ikke plukke opp noe mer
		DropHoldingItem();

		Item->SetActorEnableCollision(false);//Skrur av collision

		//UE_LOG(LogTemp, Warning, TEXT("Dropped item is %s"), *DroppedItem->GetName());

		if (Item == Torch && DroppedItem != Torch) {
			ATorchActor* TorchActor = Cast<ATorchActor>(Item);
			Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("TorchSocket"));//Attach torch til main character
			bHoldingTorch = true;
			UE_LOG(LogTemp, Warning, TEXT("Torch picked up"));
			if(TorchActor == nullptr) return;
			bTorchLit = TorchActor->bTorchLit;
		}
		else if (Item == Plank && DroppedItem != Plank) {
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
	else if (bHoldingTorch == true) {
		DropItem(Torch);
	}
}

void AMainCharacter::DropItem(AActor* Item)//F.M
{
	if (Item) {
		Item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach item fra main character
		Item->SetActorEnableCollision(true);//Skrur på collision igjen

		FVector CharacterLocation = GetMesh()->GetComponentLocation() - FVector(0.f, 0.f, 10.f);
		FVector DropLocation = CharacterLocation + (GetMesh()->GetForwardVector() * 60.f);

		if (Item == Plank) {
			DropRotation = FRotator(0.f, GetMesh()->GetRelativeRotation().Yaw + 90.f, 270.f);
			bHoldingPlank = false;
			UE_LOG(LogTemp, Warning, TEXT("Plank dropped"));
			DroppedItem = Plank;
		}
		else if (Item == Torch) {
			DropRotation = FRotator(-85.f, GetMesh()->GetRelativeRotation().Yaw - 45.f, 0.f);
			bHoldingTorch = false;
			Torch->TorchFlameOff();
			UE_LOG(LogTemp, Warning, TEXT("Torch dropped"));
			DroppedItem = Torch;
		}

		Item->SetActorRotation(FQuat(DropRotation));
		Item->SetActorLocation(DropLocation);
	}
}

void AMainCharacter::PlacePlank()//F.M 
{
	if (bHoldingPlank == true && InTriggerBox == true) {

		Plank->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach planken fra main character
		Plank->SetActorEnableCollision(true);//Skrur på collision igjen

		Plank->SetActorLocation(Location);//Plasserer planken på drop lokasjonen
		Plank->SetActorScale3D(FVector(13.f));//Gir planke riktig størrelse
		Plank->SetActorRelativeRotation(FQuat(Rotation));//Gir planke riktig rotasjon

		bHoldingPlank = false;
		UE_LOG(LogTemp, Warning, TEXT("Plank placed"));
	}
}

void AMainCharacter::StartInteract() {//F.M
	//UE_LOG(LogTemp, Warning, TEXT("Interact!"));
	HitBox->SetGenerateOverlapEvents(true);//Skrur på hitboxen så den registrerer om noe er i den
	//Interacting = true;
}

void AMainCharacter::StopInteract()//F.M
{
	//UE_LOG(LogTemp, Warning, TEXT("Stop Interact!"));
	HitBox->SetGenerateOverlapEvents(false);//Skrur av hitboxen igjen
}

void AMainCharacter::OnOverlapHitBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) //F.M
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
	if (OtherActor->IsA(ATorchActor::StaticClass()))//Hvis det er torch
	{
		ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
		Torch = TorchHit;
		AttachItem(Torch);
		UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchLit ? TEXT("true") : TEXT("false"));
	}
	else if (OtherActor->IsA(APlankActor::StaticClass()))//Hvis det er planke
	{
		APlankActor* PlankHit = Cast<APlankActor>(OtherActor);
		Plank = PlankHit;
		AttachItem(Plank);
	}
	else if (OtherActor->IsA(ATorchHolderActor::StaticClass()))//Hvis det er en torch holder
	{
		ATorchHolderActor* TorchHolder = Cast<ATorchHolderActor>(OtherActor);
		if (bHoldingTorch == true) {//Hvis karakteren holder torch
			if (Torch->bTorchLit == true) {//Hvis torch er lit
				Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Karakteren slutter å holde torch
				Torch->SetActorEnableCollision(true);//Skrur på collision igjen
				Torch->SetActorLocation(TorchHolder->GetTorchPlacementPoint().GetLocation());
				Torch->SetActorRotation(TorchHolder->GetTorchPlacementPoint().GetRotation());//Setter torch i torch holder
				TorchHolder->SetTorchActor(Torch);
				TorchHolder->bHasATorch = true;
				DroppedItem = Torch;
				UE_LOG(LogTemp,Warning,TEXT("%s"),*Torch->GetName());
				bHoldingTorch = false;
				Torch->TorchFlameOn();
			}
			else UE_LOG(LogTemp, Warning, TEXT("Door will not open because the torch is not lit"));
		}
		else if(GetTorchActor() != nullptr)
		{
			Torch = TorchHolder->GetTorchActor();
			TorchHolder->bHasATorch = false;
			UE_LOG(LogTemp,Warning,TEXT("%s"),*Torch->GetName());
			AttachItem(Torch);
			UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchLit ? TEXT("true") : TEXT("false"));
		}
	}
	else if (OtherActor->IsA(ASpiderWebActor::StaticClass()))
	{
		if (Torch->bTorchLit == true)
		{
			//Hvis torch er lit
			{//Hvis det er spider web
				ASpiderWebActor* Web = Cast<ASpiderWebActor>(OtherActor);
				//UE_LOG(LogTemp, Warning, TEXT("player detects %s"), *OtherActor->GetName());
				if (Web->bBurning == false) {
					Web->StartBurnWeb();
				}
			}
		}
	}
	else if (OtherActor->IsA(ABrazierActor::StaticClass())) {//Hvis det er brazier
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




ATorchActor* AMainCharacter::GetTorchActor()
{
	if(Torch != nullptr)
		return Torch;

	return nullptr;
}

void AMainCharacter::AttackStart()
{
	AttackBoxComponent->SetGenerateOverlapEvents(true);
	bIsAttacking = true;
}

void AMainCharacter::AttackEnd()
{
	AttackBoxComponent->SetGenerateOverlapEvents(false);
	bIsAttacking = false;
}

void AMainCharacter::OnOverlapAttackBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("Attack"));
	if(OtherActor->IsA(ASpiderCharacter::StaticClass()))
	{
		ASpiderCharacter* SpiderHit = Cast<ASpiderCharacter>(OtherActor);
		if(bHoldingTorch)
		{
			if(bTorchLit) //torch on fire
				SpiderHit->GetHit(2);
			else //torch not on fire
				SpiderHit->GetHit(1);
		}
		else if(bHoldingPlank) //plank
			SpiderHit->GetHit(3);
		else //melee
			SpiderHit->GetHit(0);
	}
	UE_LOG(LogTemp,Error,TEXT("Actor hit %s"), *OtherActor->GetName());
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
