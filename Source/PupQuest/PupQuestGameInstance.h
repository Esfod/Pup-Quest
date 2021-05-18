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
		FVector RespawnPoint;

	bool NewSpawn = false;

	bool bGameStarted = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 SecretsFound = 0;
};
