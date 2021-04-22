// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PupQuestGameInstance.generated.h"

UCLASS()
class PUPQUEST_API UPupQuestGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		FVector RespawnPoint = FVector(11000.f, 9490.f, 620.f);

	bool NewSpawn = false;
};
