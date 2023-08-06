// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManager/InputManagerComponent.h"
#include "InputManager/InputContext.h"
#include "GameFramework/PlayerInput.h"

// Sets default values for this component's properties
UInputManagerComponent::UInputManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for (EInputControlMode Mode : TEnumRange<EInputControlMode>())
	{
		InputContextClasses.Add(Mode, UInputContext::StaticClass());
	}
	IsInputAllowed = true;

	CurrentControlMode = EInputControlMode::MAX;
}

// Called when the game starts
void UInputManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UInputManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(CurrentContext) CurrentContext->TickComponent(DeltaTime);
	// ...
}

UInputContext* UInputManagerComponent::GetCurrentContext() const { return CurrentContext; }
EInputControlMode UInputManagerComponent::GetControlMode() const { return CurrentControlMode; }
UInputComponent* UInputManagerComponent::GetInputComponent() const { return InputComponentRef; }

void UInputManagerComponent::SetControlMode_Implementation(EInputControlMode Value, UInputData* Data)
{
	//if (Value == CurrentControlMode) return;
	CurrentControlMode = Value;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Updated mode to %i"), CurrentControlMode));
	if (CurrentContext) CurrentContext->EndContext();
	CurrentContext = AllContexts[CurrentControlMode];
	if (CurrentContext) CurrentContext->StartContext(Data);
}

bool UInputManagerComponent::GetIsInputAllowed() const
{
	if (!CurrentContext) return false;
	return IsInputAllowed;
}

void UInputManagerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent, APlayerController* PlayerController)
{
	if (IsValid(PlayerController)) { ControllerRef = PlayerController; } else { UE_LOG(LogTemp, Error, TEXT("PlayerInputComponent %s recieved invalid PlayerController!"), *GetOwner()->GetName()); }
	for (const TPair<EInputControlMode, TSubclassOf<UInputContext>>& pair : InputContextClasses) {
		UInputContext* NewContext = NewObject<UInputContext>(this, pair.Value);
		NewContext->Setup(this, Cast<APawn>(GetOwner()), ControllerRef);
		AllContexts.Add(pair.Key, NewContext);
	}
	SetControlMode(EInputControlMode::Selection);

	InputComponentRef = PlayerInputComponent;
	PlayerInputComponent->BindAction("PrimaryAction",	IE_Pressed,  this, &UInputManagerComponent::PrimaryAction_Pressed);
	PlayerInputComponent->BindAction("PrimaryAction",	IE_Released, this, &UInputManagerComponent::PrimaryAction_Released);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed,  this, &UInputManagerComponent::SecondaryAction_Pressed);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Released, this, &UInputManagerComponent::SecondaryAction_Released);
	PlayerInputComponent->BindAction("TertiaryAction",	IE_Pressed,  this, &UInputManagerComponent::TertiaryAction_Pressed);
	PlayerInputComponent->BindAction("TertiaryAction",	IE_Released, this, &UInputManagerComponent::TertiaryAction_Released);
}

void UInputManagerComponent::PrimaryAction_Pressed_Implementation()
{
	if (GetIsInputAllowed()) CurrentContext->PrimaryAction_Pressed(IsShiftDown(), IsCtrlDown(), IsAltDown());
}

void UInputManagerComponent::PrimaryAction_Released_Implementation()
{
	if (GetIsInputAllowed()) CurrentContext->PrimaryAction_Released(IsShiftDown(), IsCtrlDown(), IsAltDown());
}

void UInputManagerComponent::SecondaryAction_Pressed_Implementation()
{
	if (GetIsInputAllowed()) CurrentContext->SecondaryAction_Pressed(IsShiftDown(), IsCtrlDown(), IsAltDown());
}

void UInputManagerComponent::SecondaryAction_Released_Implementation()
{
	if (GetIsInputAllowed()) CurrentContext->SecondaryAction_Released(IsShiftDown(), IsCtrlDown(), IsAltDown());
}

void UInputManagerComponent::TertiaryAction_Pressed_Implementation()
{
	if (GetIsInputAllowed()) CurrentContext->TertiaryAction_Pressed(IsShiftDown(), IsCtrlDown(), IsAltDown());
}

void UInputManagerComponent::TertiaryAction_Released_Implementation()
{
	if (GetIsInputAllowed()) CurrentContext->TertiaryAction_Released(IsShiftDown(), IsCtrlDown(), IsAltDown());
}

bool UInputManagerComponent::IsShiftDown() const
{
	return ControllerRef->PlayerInput->IsShiftPressed();
}

bool UInputManagerComponent::IsCtrlDown() const
{
	return ControllerRef->PlayerInput->IsCtrlPressed();
}

bool UInputManagerComponent::IsAltDown() const
{
	return ControllerRef->PlayerInput->IsAltPressed();
}