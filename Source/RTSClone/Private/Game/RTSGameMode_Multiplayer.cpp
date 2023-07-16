// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSGameMode_Multiplayer.h"
#include "Game/RTSPlayerController.h"
#include "Game/RTSPlayerState.h"

void ARTSGameMode_Multiplayer::StartMatch()
{
	Super::StartMatch();
}

void ARTSGameMode_Multiplayer::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	ARTSPlayerController* Controller = Cast<ARTSPlayerController>(NewPlayer);
	if (Controller) {
		int32 Index = ActivePlayerList.AddUnique(NewPlayer);
		Controller->SetGenericTeamId(Index+3);
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("Added player on team %i!"), (Index+3)));
	}
	ARTSPlayerState* NewState = NewPlayer->GetPlayerState<ARTSPlayerState>();
	if (NewState) {
		NewState->SetupNewState(AllUnitTypesData);
	}
}
