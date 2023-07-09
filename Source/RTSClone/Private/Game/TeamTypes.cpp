// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TeamTypes.h"

const FColor FDefaultTeamColors::None(32, 32, 32);
const FColor FDefaultTeamColors::Neutral(64, 64, 64);
const FColor FDefaultTeamColors::Hostile(255, 0, 0);
const FColor FDefaultTeamColors::Team1(255, 128, 128);
const FColor FDefaultTeamColors::Team2(128, 255, 128);
const FColor FDefaultTeamColors::Team3(128, 128, 255);
const FColor FDefaultTeamColors::Team4(255, 255, 128);
const FColor FDefaultTeamColors::Team5(255, 128, 255);
const FColor FDefaultTeamColors::Team6(128, 255, 255);
const FColor FDefaultTeamColors::Team7(255, 128, 0);
const FColor FDefaultTeamColors::Team8(255, 0, 128);
const FColor FDefaultTeamColors::Attitude_Friendly(0, 255, 255);
const FColor FDefaultTeamColors::Attitude_Neutral(128, 128, 128);
const FColor FDefaultTeamColors::Attitude_Hostile(255, 0, 0);

RTSCLONE_API FColor FDefaultTeamColors::GetTeamColor(ERTSTeam Team)
{
	switch (Team) {
		case ERTSTeam::None:	return FDefaultTeamColors::None;
		case ERTSTeam::Neutral:	return FDefaultTeamColors::Neutral;
		case ERTSTeam::Hostile:	return FDefaultTeamColors::Hostile;
		case ERTSTeam::Team1:	return FDefaultTeamColors::Team1;
		case ERTSTeam::Team2:	return FDefaultTeamColors::Team2;
		case ERTSTeam::Team3:	return FDefaultTeamColors::Team3;
		case ERTSTeam::Team4:	return FDefaultTeamColors::Team4;
		case ERTSTeam::Team5:	return FDefaultTeamColors::Team5;
		case ERTSTeam::Team6:	return FDefaultTeamColors::Team6;
		case ERTSTeam::Team7:	return FDefaultTeamColors::Team7;
		case ERTSTeam::Team8:	return FDefaultTeamColors::Team8;
		default:				return FDefaultTeamColors::None;
	}
}

RTSCLONE_API FColor FDefaultTeamColors::GetAttitudeColor(ETeamAttitude::Type Attitude)
{
	switch (Attitude) {
		case ETeamAttitude::Friendly:	return FDefaultTeamColors::Attitude_Friendly;
		case ETeamAttitude::Neutral:	return FDefaultTeamColors::Attitude_Neutral;
		case ETeamAttitude::Hostile:	return FDefaultTeamColors::Attitude_Hostile;
		default: return FDefaultTeamColors::Attitude_Neutral;
	}
}

RTSCLONE_API FColor FTeamColors::GetTeamColor(ERTSTeam Team) const
{
	switch (Team) {
		case ERTSTeam::None:	return None;
		case ERTSTeam::Neutral:	return Neutral;
		case ERTSTeam::Hostile:	return Hostile;
		case ERTSTeam::Team1:	return Team1;
		case ERTSTeam::Team2:	return Team2;
		case ERTSTeam::Team3:	return Team3;
		case ERTSTeam::Team4:	return Team4;
		case ERTSTeam::Team5:	return Team5;
		case ERTSTeam::Team6:	return Team6;
		case ERTSTeam::Team7:	return Team7;
		case ERTSTeam::Team8:	return Team8;
		default: return None;
	}
}

RTSCLONE_API void FTeamColors::SetTeamColor(ERTSTeam Team, FColor Value)
{
	switch (Team) {
		case ERTSTeam::None:	None = Value; break;
		case ERTSTeam::Neutral:	Neutral = Value; break;
		case ERTSTeam::Hostile:	Hostile = Value; break;
		case ERTSTeam::Team1:	Team1 = Value; break;
		case ERTSTeam::Team2:	Team2 = Value; break;
		case ERTSTeam::Team3:	Team3 = Value; break;
		case ERTSTeam::Team4:	Team4 = Value; break;
		case ERTSTeam::Team5:	Team5 = Value; break;
		case ERTSTeam::Team6:	Team6 = Value; break;
		case ERTSTeam::Team7:	Team7 = Value; break;
		case ERTSTeam::Team8:	Team8 = Value; break;
		default: return;
	}
}

RTSCLONE_API FColor FTeamColors::GetAttitudeColor(ETeamAttitude::Type Attitude)
{
	switch (Attitude) {
		case ETeamAttitude::Friendly:	return FDefaultTeamColors::Attitude_Friendly;
		case ETeamAttitude::Neutral:	return FDefaultTeamColors::Attitude_Neutral;
		case ETeamAttitude::Hostile:	return FDefaultTeamColors::Attitude_Hostile;
		default: return FDefaultTeamColors::Attitude_Neutral;
	}
}