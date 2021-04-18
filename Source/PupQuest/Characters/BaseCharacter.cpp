// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ABaseCharacter::ABaseCharacter()
{	
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->InitBoxExtent(FVector(50.f, 50.f, 70.f));
	HitBox->SetupAttachment(GetMesh());
	HitBox->SetGenerateOverlapEvents(false);

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
	//unviersal death and sound
	
}

void ABaseCharacter::IsCharacterDead()
{
	if(Health == 0.f) bCharacterDead = true;
    	bCharacterDead = false;
}