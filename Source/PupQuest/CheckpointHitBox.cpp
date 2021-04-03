// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointHitBox.h"
#include "Characters/MainCharacter.h"

ACheckpointHitBox::ACheckpointHitBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ACheckpointHitBox::OnOverlap);

}

void ACheckpointHitBox::OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor) {

	//if (OtherActor->IsA(AMainCharacter::StaticClass())) {
	//	AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
	//	Main->CheckpointLocation = true;
	//	//Main->NewLocation = this->GetMesh()->GetActorLocation();//GetActorLocation();
	//	//Main->HandleDeath();
	//	//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	//}
}