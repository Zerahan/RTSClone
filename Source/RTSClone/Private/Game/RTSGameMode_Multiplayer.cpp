// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSGameMode_Multiplayer.h"
#include "Game/RTSPlayerController.h"
#include "Game/RTSPlayerState.h"
#include "Engine/DataTable.h"
#include "Data/UnitData_Static.h"


void ARTSGameMode_Multiplayer::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	if(!AllUnitTypesData->IsValidLowLevel()) return;
	UnitDataListIDs = AllUnitTypesData->GetRowNames();
	for (int32 i = 0; i < UnitDataListIDs.Num(); i++) {
		FUnitData_StaticStruct* Row = AllUnitTypesData->FindRow<FUnitData_StaticStruct>(UnitDataListIDs[i], "");
		UUnitData_Static* UnitRef = NewObject<UUnitData_Static>(this);
		UnitRef->LoadData(*Row);
		UnitDataList.Add(UnitRef);
	}
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

UUnitData_Static* ARTSGameMode_Multiplayer::GetUnitDataForID(FName ID) const
{
	
	int32 Index = UnitDataListIDs.Find(ID);
	if(Index == INDEX_NONE) return nullptr;
	return UnitDataList[Index];
}
