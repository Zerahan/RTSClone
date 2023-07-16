// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitStructure_Basic_Ghost.h"
#include "Data/UnitData_Static.h"

// Sets default values
AUnitStructure_Basic_Ghost::AUnitStructure_Basic_Ghost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitStructure_Basic_Ghost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitStructure_Basic_Ghost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AUnitStructure_Basic_Ghost::SetupUnitFromDataObject_Implementation(UUnitData_Static* StaticData) {
	StaticDataRef = StaticData;
	return true;
}

UUnitData_Static* AUnitStructure_Basic_Ghost::GetUnitStaticData_Implementation() const { return StaticDataRef; }

