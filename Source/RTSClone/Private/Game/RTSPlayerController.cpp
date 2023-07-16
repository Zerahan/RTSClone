// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSPlayerController.h"

void ARTSPlayerController::BeginPlay()
{
	SetShowMouseCursor(true);
}

void ARTSPlayerController::SetGenericTeamId(const FGenericTeamId& Value) { TeamID = Value; }

FGenericTeamId ARTSPlayerController::GetGenericTeamId() const { return TeamID; }
