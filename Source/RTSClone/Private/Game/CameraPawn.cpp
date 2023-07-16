// Fill out your copyright notice in the Description page of Project Settings.
#define DEBUGMESSAGE(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}

#include "Game/CameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/ArrowComponent.h"
#include "InputManager/InputManagerComponent.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	NetPriority = 3.0f;

	BaseEyeHeight = 0.0f;
	bCollideWhenPlacing = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent0"));
	CollisionComponent->InitSphereRadius(35.0f);
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->SetShouldUpdatePhysicsVolume(true);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->bDynamicObstacle = true;

	RootComponent = CollisionComponent;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("MovementComponent0");
	MovementComponent->UpdatedComponent = CollisionComponent;

	ZoomLevel = 4;
	ZoomLevel_Min = 1;
	ZoomLevel_Max = 10;
	ZoomLevel_Override = 0;
	CameraArmLength_Min = 1000.f;
	CameraArmLength_Max = 8000.f;

	CameraPanSpeed_Default = MovementComponent->GetMaxSpeed();
	CameraPanSpeed = CameraPanSpeed_Default;
	CameraPanSpeedMultiplier = 2.f;
	CameraPanSpeed_Override = 0;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	CameraArm_Terrain = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm_Terrain"));
	if (CameraArm_Terrain) {
		CameraArm_Terrain->SetupAttachment(RootComponent);
		CameraArm_Terrain->SetRelativeLocation(FVector(0, 0, 1000));
		//CameraArm_Terrain->SetUsingAbsoluteRotation(true);
		CameraArm_Terrain->SetWorldRotation(FRotator(90,0,90));
		CameraArm_Terrain->TargetArmLength = 1000;
	}

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	if (CameraArm) {
		CameraArm->SetupAttachment(CameraArm_Terrain);
		CameraArm->SetRelativeLocation(FVector(100, 0, 0));
		//CameraArm->SetUsingAbsoluteRotation(true);
		//CameraArm->SetRelativeRotation(FRotator(-45, 45, 0));
		CameraArm->SetRelativeRotation(FRotator(0, 135, -90));
		CameraArm->bDoCollisionTest = false;
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera) {
		Camera->SetupAttachment(CameraArm);
		Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	}

#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(CameraArm_Terrain);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetVisibility(true);
		ArrowComponent->SetHiddenInGame(false);
	}
#endif // WITH_EDITORONLY_DATA

	InputManagerComponent = CreateDefaultSubobject<UInputManagerComponent>(TEXT("Input Manager Component"));
	if (InputManagerComponent) {
		
	}
	UpdateCameraZoom();
	UpdateCameraPanSpeed();
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

inline uint8 ACameraPawn::GetZoomLevel() const { return ((ZoomLevel_Override != 0) ? ZoomLevel_Override : ZoomLevel); }

inline uint8 ACameraPawn::GetZoomLevel_Min() const { return ZoomLevel_Min; }

inline uint8 ACameraPawn::GetZoomLevel_Max() const { return ZoomLevel_Max; }

inline float ACameraPawn::GetCameraPanSpeed() const { return ((CameraPanSpeed_Override != 0) ? CameraPanSpeed_Override : CameraPanSpeed); }

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACameraPawn::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACameraPawn::ZoomOut);

	PlayerInputComponent->BindAxis("Zoom", this, &ACameraPawn::ZoomAxis);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACameraPawn::MoveRight);

	if (InputManagerComponent) {
		InputManagerComponent->SetupPlayerInputComponent(PlayerInputComponent, Cast<APlayerController>(GetController()));
	}
}

uint8 ACameraPawn::SetZoomLevel_Min(uint8 NewZoomLevel_Min)
{
	ZoomLevel_Min = NewZoomLevel_Min;
	return ZoomLevel_Min;
}

uint8 ACameraPawn::SetZoomLevel_Max(uint8 NewZoomLevel_Max)
{
	ZoomLevel_Max = NewZoomLevel_Max;
	return ZoomLevel_Max;
}

uint8 ACameraPawn::SetZoomLevelOverride(uint8 NewZoomLevel_Override)
{
	ZoomLevel_Override = NewZoomLevel_Override;
	UpdateCameraZoom();
	UpdateCameraPanSpeed();
	return ZoomLevel_Override;
}

float ACameraPawn::SetCameraPanSpeedOverride(float NewCameraPanSpeedOverride)
{
	CameraPanSpeed_Override = NewCameraPanSpeedOverride;
	UpdateCameraPanSpeed();
	return CameraPanSpeed_Override;
}

void ACameraPawn::ZoomAxis_Implementation(float AxisValue)
{
	if(AxisValue == 0) return;
}

void ACameraPawn::MoveForward_Implementation(float AxisValue)
{
	if (AxisValue == 0) return;
	FVector v = GetCameraForwardVector();
	//DEBUGMESSAGE("Forward: %f @ %f in (%f, %f, %f)", AxisValue, GetCameraPanSpeed(), (int32)(v.X * 10) * 0.1f, (int32)(v.Y * 10) * 0.1f, (int32)(v.Z * 10) * 0.1f);
	AddMovementInput(GetCameraForwardVector(), AxisValue);
}

void ACameraPawn::MoveRight_Implementation(float AxisValue)
{
	if (AxisValue == 0) return;
	//DEBUGMESSAGE("Right: %f @ %f", AxisValue, GetCameraPanSpeed());
	AddMovementInput(GetCameraRightVector(), AxisValue);
}

void ACameraPawn::ZoomIn_Implementation()
{
	if (ZoomLevel_Override != 0) return;
	SetZoomLevel(ZoomLevel - 1);
}

void ACameraPawn::ZoomOut_Implementation()
{
	if (ZoomLevel_Override != 0) return;
	SetZoomLevel(ZoomLevel + 1);
}

uint8 ACameraPawn::SetZoomLevel(uint8 NewZoomLevel)
{
	if(ZoomLevel == NewZoomLevel) return ZoomLevel;
	ZoomLevel = FMath::Clamp(NewZoomLevel, ZoomLevel_Min, ZoomLevel_Max);
	UpdateCameraZoom();
	UpdateCameraPanSpeed();
	return ZoomLevel;
}

void ACameraPawn::UpdateCameraZoom_Implementation()
{
	float ZoomPercent = (GetZoomLevel() - ZoomLevel_Min) / (float)(ZoomLevel_Max - ZoomLevel_Min);
	//DEBUGMESSAGE("ZoomPercent: %f (%i)", ZoomPercent, ZoomLevel);
	if (Camera->ProjectionMode == ECameraProjectionMode::Orthographic) {
		Camera->SetOrthoWidth((CameraArmLength_Max - CameraArmLength_Min) * ZoomPercent + CameraArmLength_Min);
		CameraArm->TargetArmLength = CameraArmLength_Max;
	}
	else {
		CameraArm->TargetArmLength = (CameraArmLength_Max - CameraArmLength_Min) * ZoomPercent + CameraArmLength_Min;
	}
}

void ACameraPawn::UpdateCameraPanSpeed_Implementation()
{
	float ZoomPercent = (GetZoomLevel() - ZoomLevel_Min) / (float)(ZoomLevel_Max - ZoomLevel_Min);
	CameraPanSpeed = CameraPanSpeed_Default * (1 + CameraPanSpeedMultiplier * FMath::Loge(1 + ZoomPercent));
	UFloatingPawnMovement* Move = Cast<UFloatingPawnMovement>(MovementComponent);
	Move->MaxSpeed = GetCameraPanSpeed();
	//DEBUGMESSAGE("Pan Speed: %f @ %f", CameraPanSpeed, ZoomPercent);
}

FVector ACameraPawn::GetCameraRightVector() const
{
	if (CameraArm) {
		return FVector(CameraArm->GetRightVector().X, CameraArm->GetRightVector().Y, 0).GetSafeNormal();
	}
	else {
		return GetActorRightVector();
	}
}

FVector ACameraPawn::GetCameraForwardVector() const
{
	if (CameraArm) {
		return FVector(CameraArm->GetForwardVector().X, CameraArm->GetForwardVector().Y, 0).GetSafeNormal();
	}else{
		return GetActorForwardVector();
	}
}

UPawnMovementComponent* ACameraPawn::GetMovementComponent() const
{
	return MovementComponent;
}