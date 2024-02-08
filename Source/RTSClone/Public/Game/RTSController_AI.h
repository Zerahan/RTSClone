// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Game/TeamTypes.h"
#include "RTSController_AI.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class RTSCLONE_API ARTSController_AI : public AAIController
{
	GENERATED_BODY()
	
	private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess="true"))
	ERTSTeam Team;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess="true"))
	uint8 FactionID;

	public:
	UFUNCTION(BlueprintCallable)
	uint8 GetFactionID() const;

	UFUNCTION(BlueprintCallable)
	ERTSTeam GetTeam() const;

	UFUNCTION(BlueprintCallable)
	bool ChangeTeam(ERTSTeam NewTeam);
};
