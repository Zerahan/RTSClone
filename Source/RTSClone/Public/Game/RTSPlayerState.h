// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RTSPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateAvailableConstructions);

class UDataTable;
class USelectionGroup;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API ARTSPlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* AllUnits;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<FName, bool> AvailableStructures;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<FName, bool> AvailableInfantry;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TMap<FName, bool> AvailableVehicles;

	UPROPERTY()
	TArray<AActor*> OwnedUnits;

	UPROPERTY()
	TMap<FName, int32> OwnedUnitTypes;

	UPROPERTY()
	TArray<USelectionGroup*> SavedSelectionGroups

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetupNewState(UDataTable* AllPossibleConstructedUnits);
	virtual void SetupNewState_Implementation(UDataTable* AllPossibleConstructedUnits);

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateAvailableConstructions(FName InstigatingName = NAME_None, bool IsConstructed = true);
	virtual void UpdateAvailableConstructions_Implementation(FName InstigatingName, bool IsConstructed);

	UFUNCTION(BlueprintCallable)
	UDataTable* GetDataTable_AllUnits() const;

	UFUNCTION(BlueprintCallable)
	TArray<FName> GetAvailableStructures(bool GetAll = false) const;

	UFUNCTION(BlueprintCallable)
	TArray<FName> GetAvailableInfantry(bool GetAll = false) const;

	UFUNCTION(BlueprintCallable)
	TArray<FName> GetAvailableVehicles(bool GetAll = false) const;

	UFUNCTION(BlueprintCallable)
	bool IsTypeAvailable(FName Type) const;

	UFUNCTION(BlueprintCallable)
	void RegisterPerminantAvailableType(FName Type, bool ManualUpdate = false);

	UFUNCTION(BlueprintCallable)
	void RegisterUnit(AActor* UnitRef, FName Type, bool ManualUpdate = false);

	UFUNCTION(BlueprintCallable)
	void UnregisterUnit(AActor* UnitRef, FName Type, bool ManualUpdate = false);

	UPROPERTY(BlueprintAssignable)
	FOnUpdateAvailableConstructions OnUpdateAvailableConstructions;

	friend class ARTSGameMode_Multiplayer;
};
