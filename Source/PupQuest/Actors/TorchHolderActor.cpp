// Written by 3016


#include "TorchHolderActor.h"

ATorchHolderActor::ATorchHolderActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeh Component"));
	RootComponent = StaticMeshComp;

	TorchPlacementPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Torch Placement Point"));
	TorchPlacementPoint->SetupAttachment(RootComponent);
}


ATorchActor* ATorchHolderActor::GetTorchActor() const
{
	return TorchActor;          //returns the reference torch
}

bool ATorchHolderActor::HasATorch()const
{
	return bHasATorch;			//returns the bool variable to tell if this torchholder has a torch
}

void ATorchHolderActor::SetTorchActor(ATorchActor* NewTorchActor)
{
	TorchActor = NewTorchActor; //set the reference to a torch
	if(TorchActor)              //if it gets a valid torch the torchholder will 
		bHasATorch = true;      //update the bool so say it have a torch
	else                        //if it gets a nullptr the torch will have been picked up    
		bHasATorch = false;		//update the bool so say it does NOT have a torch     
}

FTransform ATorchHolderActor::GetTorchPlacementPoint() const 
{
	return TorchPlacementPoint->GetComponentTransform(); //returns the transform of this scenecomponent
}
