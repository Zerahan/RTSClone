// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitStructure_Basic.h"
#include "Data/UnitData_Static.h"
#include "Game/RTSPlayerState.h"

// Sets default values
AUnitStructure_Basic::AUnitStructure_Basic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitStructure_Basic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitStructure_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitStructure_Basic::BeginDestroy()
{
	if(IsValid(OwningPlayer) && StaticDataRef && StaticDataRef->IsValid()) OwningPlayer->GetPlayerState<ARTSPlayerState>()->UnregisterUnit(this, StaticDataRef->GetStruct().ID);
	Super::BeginDestroy();
}

bool AUnitStructure_Basic::SetupUnitFromDataObject_Implementation(UUnitData_Static* StaticData)
{
	StaticDataRef = StaticData;
	StaticDataRef->Rename(nullptr, this);
	return true;
}

bool AUnitStructure_Basic::SetupUnit_Implementation(UUnitData_Static* StaticData, AController* Controller)
{
	Execute_SetupUnitFromDataObject(this, StaticData);
	SetOwningPlayer(Controller);
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, FString::Printf(TEXT("Unit set up!")));
	if (IsValid(OwningPlayer) && StaticDataRef && StaticDataRef->IsValid()) OwningPlayer->GetPlayerState<ARTSPlayerState>()->RegisterUnit(this, StaticDataRef->GetStruct().ID);
	return true;
}

UUnitData_Static* AUnitStructure_Basic::GetUnitStaticData_Implementation() const { return StaticDataRef; }

AController* AUnitStructure_Basic::GetOwningPlayer_Implementation() const { return OwningPlayer; }

void AUnitStructure_Basic::SetOwningPlayer(AController* Controller)
{
	OwningPlayer = Controller;
	//if (IsValid(OwningPlayer) && StaticDataRef && StaticDataRef->IsValid()) OwningPlayer->GetPlayerState<ARTSPlayerState>()->RegisterUnit(this, StaticDataRef->GetStruct().ID);
}

uint8 AUnitStructure_Basic::GetTeamID() const
{
	return uint8();
}

bool AUnitStructure_Basic::GetIsPrimaryFactory() const { return IsPrimaryFactory; }
void AUnitStructure_Basic::SetIsPrimaryFactory(bool Value)
{
	if (Value == IsPrimaryFactory) return;
	IsPrimaryFactory = Value;
	OnPrimarySet.Broadcast(Value);
}

