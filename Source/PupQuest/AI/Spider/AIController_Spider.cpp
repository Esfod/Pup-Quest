// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Spider.h"

void AAIController_Spider::BeginPlay()
{
	Super::BeginPlay(); 
	if(AIBehavior != nullptr) RunBehaviorTree(AIBehavior); //runs the BehaviorTree of the spider
}