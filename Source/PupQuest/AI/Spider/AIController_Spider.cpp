// Written by 3016


#include "AIController_Spider.h"

void AAIController_Spider::BeginPlay()
{
	Super::BeginPlay(); 
	if(AIBehavior != nullptr) RunBehaviorTree(AIBehavior); //runs the BehaviorTree of the spider
}