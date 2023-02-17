// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "RTSGeneralFunctionLibrary.generated.h"

class URTSGameInstance;

/**
 * 
 */
UCLASS(BlueprintType)
class RTSCLONE_API URTSGeneralFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static URTSGameInstance* GetRTSGameInstance(const UObject* WorldContextObject);

};
