// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Game/TeamTypes.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API ARTSPlayerController : public APlayerController , public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
	UPROPERTY()
	FGenericTeamId TeamID;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void SetGenericTeamId(const FGenericTeamId& Value);
	virtual FGenericTeamId GetGenericTeamId() const;
};
