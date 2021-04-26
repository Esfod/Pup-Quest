// Fill out your copyright notice in the Description page of Project Settings.


#include "AntCharacter.h"

AAntCharacter::AAntCharacter()
{
	
}

void AAntCharacter::Tick(float DeltaSeconds)
{
	
}

void AAntCharacter::AntGettingHit()
{
	HandleDeath();
	bCharacterDead = true;
}

void AAntCharacter::Attack(float OwnerDamage)
{
	Super::Attack(OwnerDamage);

	
}
