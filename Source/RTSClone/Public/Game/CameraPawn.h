// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "GameFramework/DefaultPawn.h"
#include "CameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
class UPawnMovementComponent;
class UArrowComponent;
class URTSHandlerComponent;

UCLASS(Blueprintable, BlueprintType, Abstract)
class RTSCLONE_API ACameraPawn : public APawn
{
	GENERATED_BODY()
	
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	uint8 ZoomLevel;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	uint8 ZoomLevel_Override;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	uint8 ZoomLevel_Min;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	uint8 ZoomLevel_Max;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float CameraArmLength_Min;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float CameraArmLength_Max;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float CameraPanSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float CameraPanSpeedMultiplier;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	float CameraPanSpeed_Override;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	float CameraPanSpeed_Default;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm_Terrain;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

#if WITH_EDITORONLY_DATA
	/** Component shown in the editor only to indicate character facing */
	UPROPERTY()
	UArrowComponent* ArrowComponent;
#endif
	
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	URTSHandlerComponent* ControlHandlerComponent;

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	uint8 GetZoomLevel() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetZoomLevel_Min() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetZoomLevel_Max() const;

	UFUNCTION(BlueprintCallable)
	float GetCameraPanSpeed() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	uint8 SetZoomLevel_Min(uint8 NewZoomLevel_Min);

	UFUNCTION(BlueprintCallable)
	uint8 SetZoomLevel_Max(uint8 NewZoomLevel_Max);

	UFUNCTION(BlueprintCallable)
	uint8 SetZoomLevelOverride(uint8 NewZoomLevel_Override);

	UFUNCTION(BlueprintCallable)
	float SetCameraPanSpeedOverride(float NewCameraPanSpeedOverride);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ZoomAxis(float AxisValue);
	virtual void ZoomAxis_Implementation(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MoveForward(float AxisValue);
	virtual void MoveForward_Implementation(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MoveRight(float AxisValue);
	virtual void MoveRight_Implementation(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ZoomIn();
	virtual void ZoomIn_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ZoomOut();
	virtual void ZoomOut_Implementation();

	UFUNCTION(BlueprintCallable)
	uint8 SetZoomLevel(uint8 NewZoomLevel);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateCameraZoom();
	virtual void UpdateCameraZoom_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateCameraPanSpeed();
	virtual void UpdateCameraPanSpeed_Implementation();

	UFUNCTION(BlueprintCallable)
	FVector GetCameraForwardVector() const;
	
	UFUNCTION(BlueprintCallable)
	FVector GetCameraRightVector() const;
};
