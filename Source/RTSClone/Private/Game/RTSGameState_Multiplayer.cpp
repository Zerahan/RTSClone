// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSGameState_Multiplayer.h"
#include "Net/UnrealNetwork.h"

ARTSGameState_Multiplayer::ARTSGameState_Multiplayer()
{
	TeamColors.SetNum((int32)ERTSTeam::MAX);
	for (ERTSTeam Team : TEnumRange<ERTSTeam>()) {
		TeamColors[(uint8)Team] = FDefaultTeamColors::GetTeamColor(Team);
	}

	Attitudes = {
				/*None*/					/*Neutral*/					/*Hostile*/					/*Team1*/					/*Team2*/					/*Team3*/					/*Team4*/					/*Team5*/					/*Team6*/					/*Team7*/					/*Team8*/
	/*None*/	{ETeamAttitude::Friendly,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral },	/*None*/
	/*Neutral*/ {ETeamAttitude::Neutral,	ETeamAttitude::Friendly,	ETeamAttitude::Hostile,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral,		ETeamAttitude::Neutral },	/*Neutral*/
	/*Hostile*/ {ETeamAttitude::Hostile,	ETeamAttitude::Hostile,		ETeamAttitude::Friendly,	ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile },	/*Hostile*/
	/*Team1*/	{ETeamAttitude::Neutral,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Friendly,	ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile },	/*Team1*/
	/*Team2*/	{ETeamAttitude::Neutral,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Friendly,	ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile },	/*Team2*/
	/*Team3*/	{ETeamAttitude::Neutral,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Friendly,	ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile },	/*Team3*/
	/*Team4*/	{ETeamAttitude::Neutral,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Friendly,	ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile },	/*Team4*/
	/*Team5*/	{ETeamAttitude::Neutral,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Friendly,	ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile },	/*Team5*/
	/*Team6*/	{ETeamAttitude::Neutral,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Friendly,	ETeamAttitude::Hostile,		ETeamAttitude::Hostile },	/*Team6*/
	/*Team7*/	{ETeamAttitude::Neutral,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Friendly,	ETeamAttitude::Hostile },	/*Team7*/
	/*Team8*/	{ETeamAttitude::Neutral,	ETeamAttitude::Neutral,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Hostile,		ETeamAttitude::Friendly }	/*Team8*/
	};
}

FColor ARTSGameState_Multiplayer::GetTeamColor(ERTSTeam Team) const
{
	return TeamColors[(uint8)Team];
}

void ARTSGameState_Multiplayer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARTSGameState_Multiplayer, TeamColors);
}

ETeamAttitude::Type ARTSGameState_Multiplayer::GetAttitude(FGenericTeamId OfTeam, FGenericTeamId TowardsTeam) const
{
	if (Attitudes.IsValidIndex(OfTeam) && Attitudes[OfTeam].Attitude.IsValidIndex(TowardsTeam))  return Attitudes[OfTeam].Attitude[TowardsTeam];
	return ETeamAttitude::Hostile;
}

void ARTSGameState_Multiplayer::UpdateAttitude(FGenericTeamId OfTeam, FGenericTeamId TowardsTeam, ETeamAttitude::Type Value)
{
	if (Attitudes.IsValidIndex(OfTeam) && Attitudes[OfTeam].Attitude.IsValidIndex(TowardsTeam)) Attitudes[OfTeam].Attitude[TowardsTeam] = Value;
	if (Attitudes.IsValidIndex(TowardsTeam) && Attitudes[TowardsTeam].Attitude.IsValidIndex(OfTeam)) Attitudes[TowardsTeam].Attitude[OfTeam] = Value;
}
