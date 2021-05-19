// Written by 3016


#include "AIController_Ant.h"

void AAIController_Ant::BeginPlay()
{
	Super::BeginPlay(); 
	if(AIBehavior != nullptr) RunBehaviorTree(AIBehavior); //runs the behavior three that is selected
}