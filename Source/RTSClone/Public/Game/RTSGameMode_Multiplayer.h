// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RTSGameMode_Multiplayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API ARTSGameMode_Multiplayer : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AController*> ActivePlayerList;
	
public:
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
