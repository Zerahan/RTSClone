// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/UnitStructure_Basic.h"
#include "Data/UnitData_Static.h"

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

bool AUnitStructure_Basic::SetupUnitFromDataObject_Implementation(UUnitData_Static* StaticData) {
	StaticDataRef = StaticData;
	return true;
}

UUnitData_Static* AUnitStructure_Basic::GetUnitStaticData_Implementation() const { return StaticDataRef; }

AController* AUnitStructure_Basic::GetOwningPlayer_Implementation() const { return OwningPlayer; }

