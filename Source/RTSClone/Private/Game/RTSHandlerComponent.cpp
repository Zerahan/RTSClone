// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RTSHandlerComponent.h"
#include "Game/RTSPlayerState.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
URTSHandlerComponent::URTSHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URTSHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void URTSHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EControlMode URTSHandlerComponent::GetControlMode() const { return ControlMode; }

void URTSHandlerComponent::SetControlMode(EControlMode Value) { ControlMode = Value; OnUpdateControlMode.Broadcast(ControlMode); }

ERTSTeam URTSHandlerComponent::GetTeam() const { return MyTeam; }
void URTSHandlerComponent::SERVER_SetTeam_Implementation(ERTSTeam Value) { MyTeam = Value; }
void URTSHandlerComponent::OnRep_SetTeam(ERTSTeam Value) { }

void URTSHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &URTSHandlerComponent::TestFunction);
}

void URTSHandlerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URTSHandlerComponent, MyTeam);
}

void URTSHandlerComponent::TestFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Test")));
}

void URTSHandlerComponent::OnPrimaryPressed()
{
}

void URTSHandlerComponent::OnPrimaryReleased()
{
}

void URTSHandlerComponent::OnSecondaryPressed()
{
	SetControlMode(EControlMode::Default);
}

void URTSHandlerComponent::OnSecondaryReleased()
{
}

