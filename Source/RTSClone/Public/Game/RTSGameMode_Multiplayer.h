// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RTSGameMode_Multiplayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API ARTSGameMode_Multiplayer : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AController*> ActivePlayerList;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UDataTable* AllUnitTypesData;

	UPROPERTY()
	TArray<FName> UnitDataListIDs;

	UPROPERTY()
	TArray<class UUnitData_Static*> UnitDataList;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable)
	class UUnitData_Static* GetUnitDataForID(FName ID) const;
};
