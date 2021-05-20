// Written by 3016


#include "BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ABaseCharacter::ABaseCharacter()
{	
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay(); 
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::HandleDeath()
{
	//universal death and sound
	DetachFromControllerPendingDestroy();
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//all dead characters will DetachFromController and stop the Collision of them
}