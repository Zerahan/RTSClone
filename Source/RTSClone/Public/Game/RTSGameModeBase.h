// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API ARTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARTSGameModeBase();
};
