// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PupQuest/Actors/SpiderWebActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Actors/ItemsActor/PlankActor.h"
#include "PupQuest/Actors/ItemsActor/BucketActor.h"
#include "PupQuest/Actors/TorchHolderActor.h"
#include "PupQuest/Actors/BrazierActor.h"
#include "PupQuest/Actors/WellActor.h"
#include "PupQuest/Actors/SecretChestActor.h"
#include "PupQuest/Actors/ItemsActor/BarrelActor.h"


#include "PupQuest/PupQuestGameInstance.h"

#include "PupQuest/Characters/SpiderCharacter.h"
#include "PupQuest/Characters/AntCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

#include "MediaPlayer.h"


//#include "PupQuest/Hud/P_Torch"

AMainCharacter::AMainCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(0.f, -30.f, 15.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritYaw = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArm);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(GetMesh());
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapHitBox);

	AttackBoxComponent = CreateDefaultSubobject<UBoxComponent>("Attack HitBox");
	AttackBoxComponent->SetupAttachment(GetMesh());
	//AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Attack_Box_Attach")); //TODO Add when attack-animation is implemented
	AttackBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapAttackBox);
	AttackBoxComponent->SetGenerateOverlapEvents(false);

	//3001==============
	PushingBarrelSound = CreateDefaultSubobject<UAudioComponent>(TEXT("PushingBarrelSound"));
	PushingBarrelSound->SetupAttachment(RootComponent);
	PushingBarrelSound->SetSound(PushingBarrelSoundBase);

	MenuMusic = CreateDefaultSubobject<UAudioComponent>(TEXT("MenuMusic"));
	MenuMusic->SetupAttachment(RootComponent);
	MenuMusic->SetSound(MenuMusicBase);

	IntroSound = CreateDefaultSubobject<UAudioComponent>(TEXT("IntroSound"));
	IntroSound->SetupAttachment(RootComponent);
	IntroSound->SetSound(IntroSoundBase);

	CutsceneSound = CreateDefaultSubobject<UAudioComponent>(TEXT("CutsceneSound"));
	CutsceneSound->SetupAttachment(RootComponent);
	CutsceneSound->SetSound(CutsceneSoundBase);
    //==================
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

	PlayerInputComponent->BindAction("HealthBoost",IE_Pressed,this, &AMainCharacter::UnlimtedHealth);	
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	AttackBoxComponent->SetGenerateOverlapEvents(false);
	HitBox->SetGenerateOverlapEvents(false);

	//(3001) If the player has passed through a checkpoint, the player will instantly teleport to that location when respawning
	//=========================
	UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
	//UE_LOG(LogTemp, Warning, TEXT("Game started is %s"), GameInstance->bGameStarted ? TEXT("true") : TEXT("false"));
	if (GameInstance->NewSpawn == true) {
		SetActorLocation(FVector(GameInstance->RespawnPoint));
	}
	
	NormalWalkMaxSpeed = GetMovementComponent()->GetMaxSpeed();
	UGameplayStatics::PlaySoundAtLocation(this, NolanBarking, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, AmbienceSound, GetActorLocation());

	PushingBarrelSound->Stop();//The sound for these started playing when the game started for some reason, so i just decided to stop the sound in begin play
	IntroSound->Stop();
	CutsceneSound->Stop();

	if (GameInstance->bGameStarted == true) {
		MenuMusic->Stop();
	}
	//=========================

	SetActorRotation(GetActorRotation()+FRotator(0.f,180.f,0.f));
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DroppedItem) {
		DroppedItem = nullptr;
	}
	
	if(Health != MaxHealth)
	{
		if(RegainHealthTimer == 0.0f)
			RegainHealthTimer = GetWorld()->GetTimeSeconds();
		if(RegainHealthTimer + TimeToRegain <= GetWorld()->GetTimeSeconds())
		{
			RegainHealth(DeltaTime);
			if(Health > MaxHealth) Health = MaxHealth;
		}
	}
	else RegainHealthTimer = 0.f;
	//UE_LOG(LogTemp,Warning,TEXT("%f Health"), Health);
}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && (Pushing == 1))
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
	if ( (Controller != nullptr) && (Value != 0.0f) && (Pushing == 1)) 
	{
		// find out which way is right
		const FRotator PlayerRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, PlayerRotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::AttachItem(AActor* Item)//(3001) Attaches the given item in the hand of the player
{
	DropHoldingItem();//Player drops an item if he holds one
	Item->SetActorEnableCollision(false);//Turns off collision
	Jump();
	UGameplayStatics::PlaySoundAtLocation(this, PickUpItem, GetActorLocation());
	//UE_LOG(LogTemp, Warning, TEXT("Dropped item is %s"), *DroppedItem->GetName());

	if (Item == Torch && DroppedItem != Torch) {
		ATorchActor* TorchActor = Cast<ATorchActor>(Item);
		ItemSocket = FName("TorchSocket");
		bHoldingTorch = true;
		UE_LOG(LogTemp, Warning, TEXT("Torch picked up"));
		if (TorchActor == nullptr) return;
		bTorchLit = TorchActor->bTorchActorLit;
	}
	else if (Item == Plank && DroppedItem != Plank) {
		ItemSocket = FName("PlankSocket");
		bHoldingPlank = true;
		UE_LOG(LogTemp, Warning, TEXT("Plank picked up"));
	}
	else if (Item == Bucket && DroppedItem != Bucket) {
		ABucketActor* BucketActor = Cast<ABucketActor>(Item);
		ItemSocket = FName("BucketSocket");
		bHoldingBucket = true;
		UE_LOG(LogTemp, Warning, TEXT("Bucket picked up"));
	}
	Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, ItemSocket);//Attach item to main character
}

void AMainCharacter::DropHoldingItem()//(3001)If the player is holding one of these items the player will drop it
{
	if (bHoldingPlank == true) {
		DropItem(Plank);
	}
	else if (bHoldingTorch == true) {
		DropItem(Torch);
	}
	else if (bHoldingBucket == true) {
		DropItem(Bucket);
	}
}

void AMainCharacter::DropItem(AActor* Item)//3001
{
	if (Item) {
		UGameplayStatics::PlaySoundAtLocation(this, PlaceItem, GetActorLocation());
		Item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach item fra main character
		Item->SetActorEnableCollision(true);//Turns on collision

		FVector CharacterLocation = GetMesh()->GetComponentLocation();

		if (Item == Plank) {
			DropRotation = FRotator(0.f, GetActorRotation().Yaw + 90.f, 270.f);
			ItemLocationAdjustment = FVector(0.f, 0.f, -10.f);//Adjusts the height of the plank when it gets dropped
			bHoldingPlank = false;
			GetCharacterMovement()->MaxWalkSpeed = NormalWalkMaxSpeed;
			//UE_LOG(LogTemp, Warning, TEXT("Plank dropped"));
		}
		else if (Item == Torch) {
			DropRotation = FRotator(-85.f, GetActorRotation().Yaw + 45.f, 0.f);// Sets the rotation of the torch when it is dropped
			ItemLocationAdjustment = FVector(0.f, 0.f, -9.f) + GetMesh()->GetRightVector() * 40;//Adjusts the height of the torch when it gets dropped
			bHoldingTorch = false;
			Torch->TorchFlameOff();
			//UE_LOG(LogTemp, Warning, TEXT("Torch dropped"));
		}
		else if (Item == Bucket) {
			DropRotation = FRotator(0.f, GetActorRotation().Yaw, 0.f);// Sets the rotation of the bucket when it is dropped
			ItemLocationAdjustment = FVector(0.f, 0.f, -3.f) + GetMesh()->GetRightVector() * 50;//Adjusts the height of the bucket when it gets dropped
			bHoldingBucket = false;
			//UE_LOG(LogTemp, Warning, TEXT("Bucket dropped"));
		}
		Item->SetActorEnableCollision(true);
		DroppedItem = Item;

		FVector DropLocation = CharacterLocation + (GetMesh()->GetForwardVector() * 30.f) + ItemLocationAdjustment;//Sets the location where the item will get dropped
		Item->SetActorRotation(FQuat(DropRotation));
		Item->SetActorLocation(DropLocation);
	}
}

void AMainCharacter::PlacePlank()//3001
{
	if (bHoldingPlank == true && InPlankTriggerBox == true) {
		UGameplayStatics::PlaySoundAtLocation(this, PlaceItem, GetActorLocation());

		Plank->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach plank from main character

		Plank->SetActorLocation(PlacePlankLocation);//Places the plank on the right location
		Plank->SetActorScale3D(FVector(13.f));//Gives plank the right scale
		Plank->SetActorRelativeRotation(FQuat(PlacePlankRotation));//Gives plank the right rotation

		Plank->SetActorEnableCollision(true);//Turns on collision
		bHoldingPlank = false;
		UE_LOG(LogTemp, Warning, TEXT("Plank placed"));
		GetCharacterMovement()->MaxWalkSpeed = NormalWalkMaxSpeed;
	}
}

void AMainCharacter::StartInteract()//3001
{
	//UE_LOG(LogTemp, Warning, TEXT("Interact!"));
	HitBox->SetGenerateOverlapEvents(true);//Turns on the hitbox to see if something is in it
}

void AMainCharacter::StopInteract()//3001
{
	//UE_LOG(LogTemp, Warning, TEXT("Stop Interact!"));
	HitBox->SetGenerateOverlapEvents(false);//Turns off the hitbox
}

void AMainCharacter::OnOverlapHitBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) //(3001)A box component that uses overlap event to detect items you can interact with
{
	if (Pushing == 1)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
		if (OtherActor->IsA(ATorchActor::StaticClass()) && !bHoldingTorch)//If it is a torch
			{
			ATorchActor* TorchHit = Cast<ATorchActor>(OtherActor);
			Torch = TorchHit;
			AttachItem(Torch);
			//UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchActorLit ? TEXT("true") : TEXT("false"));
			}
		else if (OtherActor->IsA(APlankActor::StaticClass()) && !bHoldingPlank)//If it is a plank
			{
			APlankActor* PlankHit = Cast<APlankActor>(OtherActor);
			Plank = PlankHit;
			GetCharacterMovement()->MaxWalkSpeed = HoldingPlankSpeed;
			AttachItem(Plank);
			}
		else if (OtherActor->IsA(ABucketActor::StaticClass()) && !bHoldingBucket)//If it is a bucket
			{
			ABucketActor* BucketHit = Cast<ABucketActor>(OtherActor);
			Bucket = BucketHit;
			AttachItem(Bucket);
			}
		else if (OtherActor->IsA(ATorchHolderActor::StaticClass()))//If it is a torch holder
		{
			ATorchHolderActor* TorchHolder = Cast<ATorchHolderActor>(OtherActor);
			if (TorchHolder->GetTorchActor() != nullptr && !bHoldingTorch)		//checks if the torchholder is full, and that the player dose not hold a torch
				{
				Torch = TorchHolder->GetTorchActor();							//gets the reference to the torchholder's torch and saves it
				TorchHolder->SetTorchActor(nullptr);							//removes the refrence from the torchholder
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *Torch->GetName());
				AttachItem(Torch);												//attaches the torch from the torch holder to the player's hand
				//UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchActorLit ? TEXT("true") : TEXT("false"));
				}
			else if (TorchHolder->GetTorchActor() == nullptr && bHoldingTorch && Torch->bTorchActorLit)
			{
					//If the character is holding a torch and If torch is lit
					Torch->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);//Detach torch fra main character
					Torch->SetActorEnableCollision(false);//Turns off collision
					Torch->SetActorLocation(TorchHolder->GetTorchPlacementPoint().GetLocation());//Sets torch in the right location
					Torch->SetActorRotation(TorchHolder->GetTorchPlacementPoint().GetRotation());//Gives torch the right rotation

					TorchHolder->SetTorchActor(Torch);

					DroppedItem = Torch;
					UE_LOG(LogTemp, Warning, TEXT("%s"), *Torch->GetName());
					bHoldingTorch = false;
					//Torch->TorchFlameOn();//There was a bug here where the torch will turn off if you place it in a torch holder, so we just turn it on again here
			}
			else UE_LOG(LogTemp, Warning, TEXT("Door will not open because the torch is not lit"));
		}
		else if (OtherActor->IsA(ASpiderWebActor::StaticClass()) && bHoldingTorch == true)//If it is a spider web
		{
			if (Torch->bTorchActorLit == true)
			{
				if (Torch->bTorchActorLit == true)//If the torch is lit
				{
					ASpiderWebActor* Web = Cast<ASpiderWebActor>(OtherActor);
					if (Web->bBurning == false) //If the web is not already burning
						Web->StartBurnWeb();
				}
			}
		}
		else if (OtherActor->IsA(ABrazierActor::StaticClass()) && bHoldingTorch == true)//If it is a brazier
		{
			ABrazierActor* UBrazier = Cast<ABrazierActor>(OtherActor);
			Brazier = UBrazier;

			//UE_LOG(LogTemp, Warning, TEXT("Brazier lit is %s"), Brazier->bBrazierLit ? TEXT("true") : TEXT("false"));
			//UE_LOG(LogTemp, Warning, TEXT("Torch lit is %s"), Torch->bTorchActorLit ? TEXT("true") : TEXT("false"));
			
			if (Brazier->bBrazierLit == true && Torch->bTorchActorLit == false)//If brazier is lit and torch is not lit
				Torch->TorchFlameOn();

			else if (Brazier->bBrazierLit == false && Torch->bTorchActorLit == true)//If brazier is not lit and if torch is lit
			{
				Brazier->BrazierFlameOn();
				UGameplayStatics::PlaySoundAtLocation(this, LightBrazier, GetActorLocation());
			}
		}
		else if (OtherActor->IsA(AWellActor::StaticClass()) && bHoldingBucket == true) //If it is a well
		{
			AWellActor* UWell = Cast<AWellActor>(OtherActor);
			Well = UWell;
			if (Bucket->bBucketFilled == false)
				Bucket->BucketFill();

		}
		else if (OtherActor->IsA(ABarrelActor::StaticClass()))
		{
			ABarrelActor* UBarrel = Cast<ABarrelActor>(OtherActor);
			//UE_LOG(LogTemp,Warning,TEXT("its a barrel"));
			Barrel = UBarrel;
			if(!UBarrel->IsLaying && bHoldingBucket)
			{
				if (Barrel->bBarrelFilled == false && Bucket->bBucketFilled == true) 
				{
					Barrel->BarrelFill();
					Bucket->BucketEmpty();
				}
			}
			else if(Barrel->IsRotateble)
			{
				Barrel->RotateBarrel();
			}
		}
		else if (OtherActor->IsA(ASecretChestActor::StaticClass()))//If it is a brazier
		{
			ASecretChestActor* Chest = Cast<ASecretChestActor>(OtherActor);
			Chest->OpenChest();
		}
	}
}

ATorchActor* AMainCharacter::GetTorchActor()
{
	if(Torch != nullptr)
		return Torch;

	return nullptr;
}

ABucketActor* AMainCharacter::GetBucketActor()
{
	if (Bucket != nullptr)
		return Bucket;

	return nullptr;
}

UPupQuestGameInstance* AMainCharacter::GetChestActor()
{
	UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
	
	if (GameInstance != nullptr)
		return GameInstance;

	return nullptr;
}

void AMainCharacter::IsPushing()
{
	if (Pushing == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Started Pushing"));
		Pushing++;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		PushingBarrelSound->Play(0.f);
	}
	else if (Pushing == 2)
	{
		PushingBarrelSound->Stop();
		UE_LOG(LogTemp, Warning, TEXT("Stopped Pushing"));
		Pushing--;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
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

void AMainCharacter::OnOverlapAttackBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(ASpiderCharacter::StaticClass()))
	{
		ASpiderCharacter* SpiderHit = Cast<ASpiderCharacter>(OtherActor);
		UE_LOG(LogTemp,Warning,TEXT("Player hits Spider"));
		if(bHoldingTorch)
		{
			UGameplayStatics::PlaySoundAtLocation(this, AttackTorch, GetActorLocation());
			if (bTorchLit) { //torch on fire
				SpiderHit->SpiderGettingHit(2);
			}
			else //torch not on fire
				SpiderHit->SpiderGettingHit(1);
		}
		else if (bHoldingPlank)//plank
		{
			UGameplayStatics::PlaySoundAtLocation(this, AttackTorch, GetActorLocation());
			SpiderHit->SpiderGettingHit(3);
		}
		else if(bHoldingBucket)
		{
			UGameplayStatics::PlaySoundAtLocation(this, AttackTorch, GetActorLocation());
			if(!Bucket->bBucketFilled)
				SpiderHit->SpiderGettingHit(4);
			else
			{
				SpiderHit->SpiderGettingHit(4);
				Bucket->bBucketFilled = false;
			}
		}
		else //melee
			SpiderHit->SpiderGettingHit(0);
	}
	else if(OtherActor->IsA(AAntCharacter::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Player hits Ant"));
		if(bHoldingBucket && Bucket->bBucketFilled)
		{
			AAntCharacter* AntCharacter = Cast<AAntCharacter>(OtherActor);
			AntCharacter->AntGettingHit();
			Bucket->bBucketFilled = false;
			Bucket->BucketEmpty();
		}
	}
}

void AMainCharacter::PlayerTakeDamage(float DamageTaken)
{
	UGameplayStatics::PlaySoundAtLocation(this, TakingDamage, GetActorLocation());
	Health -= DamageTaken;
	if(Health < 0.f)
		Health =  0.f;
	UE_LOG(LogTemp,Warning,TEXT("Players Health is %f"), Health);
	
	IsCharacterDead();
	if(bCharacterDead)
		HandleDeath();
}

void AMainCharacter::RegainHealth(float DeltaTime)
{
	Health += AmountOfHealthRegain * DeltaTime;
}

void AMainCharacter::HandleDeath()
{
	Super::HandleDeath();

	UPupQuestGameInstance* GameInstance = Cast<UPupQuestGameInstance>(GetGameInstance());
	GameInstance->bGameStarted = true;
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);//Restarts level
}

void AMainCharacter::IsCharacterDead()
{
	if(Health == 0.f)
		bCharacterDead = true;
	else
		bCharacterDead = false;
}

//Under is cheats
void AMainCharacter::UnlimtedHealth()
{
	Health = 1000000000.f;
}

void AMainCharacter::StopMenuMusic()//3001
{
	MenuMusic->Stop();
}
