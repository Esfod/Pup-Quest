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

	UPROPERTY(BlueprintReadWrite)
	bool NewSpawn = false;

	UPROPERTY(BlueprintReadWrite)
		bool bIntroPlayed = true;

	UPROPERTY(BlueprintReadWrite)
		bool bGameRestarted = false;

	UPROPERTY(BlueprintReadWrite)
	bool bGameStarted = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 SecretsFound = 0;

	UPROPERTY(BlueprintReadWrite)
	bool BeetrootFound = false;

	UPROPERTY(BlueprintReadWrite)
	bool CarrotFound = false;

	UPROPERTY(BlueprintReadWrite)
	bool PotatoFound = false;
};
