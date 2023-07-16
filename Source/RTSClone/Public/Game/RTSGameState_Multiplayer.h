// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Game/TeamTypes.h"
#include "RTSGameState_Multiplayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API ARTSGameState_Multiplayer : public AGameState
{
	GENERATED_BODY()

	UPROPERTY(Replicated, SaveGame)//, ReplicatedUsing = OnRep_SetTeamColors)
	TArray<FColor> TeamColors;

	UPROPERTY(Replicated, SaveGame)//, ReplicatedUsing = OnRep_SetTeamColors)
	TArray<FTeamAttitude> Attitudes;
	
public:
	ARTSGameState_Multiplayer();
	//UFUNCTION()
	//void OnRep_SetTeamColors();

	UFUNCTION(BlueprintCallable)
	FColor GetTeamColor(ERTSTeam Team) const;

	UFUNCTION(BlueprintCallable)
	FColor GetTeamIDColor(uint8 TeamID) const;

	UFUNCTION(BlueprintCallable)
	FColor GetTeamColorFromController(AController* Controller) const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	ETeamAttitude::Type GetAttitude(FGenericTeamId OfTeam, FGenericTeamId TowardsTeam) const;

	UFUNCTION(BlueprintCallable)
	void UpdateAttitude(FGenericTeamId OfTeam, FGenericTeamId TowardsTeam, ETeamAttitude::Type Value);
};
