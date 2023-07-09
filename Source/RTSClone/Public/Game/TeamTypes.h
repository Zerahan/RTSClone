// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GenericTeamAgentInterface.h"
#include "TeamTypes.generated.h"

UENUM(BlueprintType)
enum class ERTSTeam : uint8 {
	None	UMETA(DisplayName = "None"),
	Neutral	UMETA(DisplayName = "Civilian"),
	Hostile	UMETA(DisplayName = "Hostile"),
	Team1	UMETA(DisplayName = "Team 1"),
	Team2	UMETA(DisplayName = "Team 2"),
	Team3	UMETA(DisplayName = "Team 3"),
	Team4	UMETA(DisplayName = "Team 4"),
	Team5	UMETA(DisplayName = "Team 5"),
	Team6	UMETA(DisplayName = "Team 6"),
	Team7	UMETA(DisplayName = "Team 7"),
	Team8	UMETA(DisplayName = "Team 8"),
	MAX	UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ERTSTeam, ERTSTeam::MAX);

USTRUCT(BlueprintType)
struct FDefaultTeamColors {
	GENERATED_BODY()

	static RTSCLONE_API const FColor None;
	static RTSCLONE_API const FColor Neutral;
	static RTSCLONE_API const FColor Hostile;
	static RTSCLONE_API const FColor Team1;
	static RTSCLONE_API const FColor Team2;
	static RTSCLONE_API const FColor Team3;
	static RTSCLONE_API const FColor Team4;
	static RTSCLONE_API const FColor Team5;
	static RTSCLONE_API const FColor Team6;
	static RTSCLONE_API const FColor Team7;
	static RTSCLONE_API const FColor Team8;
	static RTSCLONE_API const FColor Attitude_Friendly;
	static RTSCLONE_API const FColor Attitude_Neutral;
	static RTSCLONE_API const FColor Attitude_Hostile;

	static RTSCLONE_API FColor GetTeamColor(ERTSTeam Team);
	static RTSCLONE_API FColor GetAttitudeColor(ETeamAttitude::Type Attitude);
};

USTRUCT(BlueprintType)
struct FTeamColors {
	GENERATED_BODY()

	FTeamColors()
		: None(FDefaultTeamColors::None)
		, Neutral(FDefaultTeamColors::Neutral)
		, Hostile(FDefaultTeamColors::Hostile)
		, Team1(FDefaultTeamColors::Team1)
		, Team2(FDefaultTeamColors::Team2)
		, Team3(FDefaultTeamColors::Team3)
		, Team4(FDefaultTeamColors::Team4)
		, Team5(FDefaultTeamColors::Team5)
		, Team6(FDefaultTeamColors::Team6)
		, Team7(FDefaultTeamColors::Team7)
		, Team8(FDefaultTeamColors::Team8)
	{};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor None;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Neutral;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Hostile;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Team1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Team2;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Team3;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Team4;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Team5;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Team6;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Team7;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FColor Team8;

	RTSCLONE_API FColor GetTeamColor(ERTSTeam Team) const;
	RTSCLONE_API void SetTeamColor(ERTSTeam Team, FColor Value);

	static RTSCLONE_API FColor GetAttitudeColor(ETeamAttitude::Type Attitude);
};
//*/

USTRUCT(BlueprintType)
struct FTeamAttitude {
	GENERATED_BODY()

	FTeamAttitude(){};

	FTeamAttitude(std::initializer_list<TEnumAsByte<ETeamAttitude::Type>> attitudes)
		: Attitude(std::move(attitudes))
	{};

	UPROPERTY(BlueprintReadOnly)
	TArray<TEnumAsByte<ETeamAttitude::Type>> Attitude;
};
//*/