// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManager/InputContext.h"

void UInputContext::TickComponent_Implementation(float DeltaTime)
{
}

AActor* UInputContext::SpawnActorFromClass_Implementation(TSubclassOf<AActor> ActorClass, FTransform Transform)
{
	if(!ActorClass) return nullptr;
	FActorSpawnParameters Params = FActorSpawnParameters();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* ActorRef = GetWorld()->SpawnActor<AActor>(ActorClass, Transform, Params);
	if(ActorRef) ActorRef->SetOwner(PawnRef);
    return ActorRef;
}

void UInputContext::StartContext_Implementation(UInputData* Data)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: Starting Context."), *GetClass()->GetFName().ToString()));
}

void UInputContext::EndContext_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: Ending Context."), *GetClass()->GetFName().ToString()));
}

void UInputContext::Setup(UInputManagerComponent* Manager, APawn* Pawn, APlayerController* Controller)
{
	InputManagerRef = Manager;
	PawnRef = Pawn;
	ControllerRef = Controller;
}
APawn* UInputContext::GetPlayerPawn() const { return PawnRef; }
APlayerController* UInputContext::GetPlayerController() const { return ControllerRef; }
UInputManagerComponent* UInputContext::GetInputManager() const { return InputManagerRef; }

void UInputContext::PrimaryAction_Pressed_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown)
{
#if WITH_EDITORONLY_DATA
	PrintInput("Primary Pressed", IsShiftDown, IsCtrlDown, IsAltDown);
#endif
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: Primary Pressed + %s%s%s"), *GetClass()->GetFName().ToString(), (IsShiftDown ? (IsCtrlDown || IsAltDown ? "Shift, " : "Shift") : ""), (IsCtrlDown ? (IsAltDown ? "Ctrl, " : "Ctrl") : ""), (IsAltDown ? "Alt" : "")));
}

void UInputContext::PrimaryAction_Released_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: Primary Released"), *GetClass()->GetFName().ToString()));
}

void UInputContext::SecondaryAction_Pressed_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: Secondary Pressed"), *GetClass()->GetFName().ToString()));
}

void UInputContext::SecondaryAction_Released_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: Secondary Released"), *GetClass()->GetFName().ToString()));
}

void UInputContext::TertiaryAction_Pressed_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: Tertiary Pressed"), *GetClass()->GetFName().ToString()));
}

void UInputContext::TertiaryAction_Released_Implementation(bool IsShiftDown, bool IsCtrlDown, bool IsAltDown)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: Tertiary Released"), *GetClass()->GetFName().ToString()));
}

#if WITH_EDITORONLY_DATA
void UInputContext::PrintInput(FString Msg, bool IsShiftDown, bool IsCtrlDown, bool IsAltDown) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%s: %s + %s%s%s"), *GetClass()->GetFName().ToString(), *Msg, (IsShiftDown ? (IsCtrlDown || IsAltDown ? "Shift, " : "Shift") : ""), (IsCtrlDown ? (IsAltDown ? "Ctrl, " : "Ctrl") : ""), (IsAltDown ? "Alt" : "")));
}
#endif
