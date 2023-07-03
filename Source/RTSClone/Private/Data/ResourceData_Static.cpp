// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ResourceData_Static.h"

bool UResourceData_Static::LoadData(FResourceData_StaticStruct Data)
{
	if (Data.IsValid()) {
		ResourceData_Static = Data;
	}
	return false;
}

FResourceData_StaticStruct UResourceData_Static::Get() const { return ResourceData_Static; }

bool UResourceData_Static::IsValid() const { return ResourceData_Static.IsValid(); }