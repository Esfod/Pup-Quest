// Written by 3016


#include "AntCharacter.h"

AAntCharacter::AAntCharacter()
{
	
}

void AAntCharacter::Tick(float DeltaSeconds)
{
	
}

void AAntCharacter::AntGettingHit()
{
	HandleDeath(); //runs handle death
	SoundLocation = FVector(0.f);
	bCharacterDead = true;
	UE_LOG(LogTemp,Warning,TEXT("Ant Dead"));
}

void AAntCharacter::Attack()
{
	Super::Attack(); //calls super to do it's code before it does this
}
