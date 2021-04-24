// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Ant.h"

void AAIController_Ant::BeginPlay()
{
	Super::BeginPlay(); 
	if(AIBehavior != nullptr) RunBehaviorTree(AIBehavior);
}