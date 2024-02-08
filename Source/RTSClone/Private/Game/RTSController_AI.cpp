// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSController_AI.h"

uint8 ARTSController_AI::GetFactionID() const { return FactionID; }

ERTSTeam ARTSController_AI::GetTeam() const { return Team; }

bool ARTSController_AI::ChangeTeam(ERTSTeam NewTeam)
{
	// if(NewTeam == Team::None) return false;
	// if(Team == NewTeam) return false;
	// if(GameSettings.CanChangeTeam()) return true;
	return false;
}
