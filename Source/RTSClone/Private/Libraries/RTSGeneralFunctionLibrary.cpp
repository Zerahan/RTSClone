// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/RTSGeneralFunctionLibrary.h"
#include "Game/RTSGameInstance.h"

URTSGameInstance* URTSGeneralFunctionLibrary::GetRTSGameInstance(const UObject* WorldContextObject) {
	if (WorldContextObject) {
		URTSGameInstance* Instance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject->GetWorld()));
		return Instance;
	}
	return nullptr;
}
