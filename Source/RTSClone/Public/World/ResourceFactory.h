// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceFactory.generated.h"

USTRUCT(BlueprintType)
struct FResourceDeposit {
	GENERATED_BODY()

	FResourceDeposit()
		: InstanceIndex(-1)
		, Amount(0)
		, MaxAmount(200)
		, CanSpread(true)
	{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 InstanceIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 Amount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 MaxAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanSpread;

	bool IsValid() {
		return InstanceIndex != -1;
	}
};

//class USceneComponent;
class UHierarchicalInstancedStaticMeshComponent;

UCLASS(BlueprintType, Blueprintable, Abstract)
class RTSCLONE_API AResourceFactory : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* OriginPoint;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* Mesh;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 TileSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float HorizontalSpacing;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float VerticalSpacing;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FVector ScaleOverride;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 MapWidth;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 MapHeight;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<FResourceDeposit> ExistingResources;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool UseHexagonalGrid;

public:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FVector MapCenter;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UBillboardComponent* Billboard;
#endif
	
public:	
	// Sets default values for this actor's properties
	AResourceFactory();

#if WITH_EDITORONLY_DATA
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int32 GetIndex(int32 X, int32 Y) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetLocation(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	FVector2D GetLocationWithOffset(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	FVector GetWorldLocation(int32 Index, int32 ZOffset = 0) const;

	UFUNCTION(BlueprintCallable)
	int32 GetInstanceIndexAt(int32 X, int32 Y) const;

	UFUNCTION(BlueprintCallable)
	bool IsValidLocation(int32 X, int32 Y) const;

	UFUNCTION(BlueprintCallable)
	bool CreateInstanceAt(int32 X, int32 Y, uint8 Amount = 1);

	UFUNCTION(BlueprintCallable)
	bool SetAmount(int32 Index, int32 Amount);
	
	UFUNCTION(BlueprintCallable)
	bool SetAmountAt(int32 X, int32 Y, int32 Amount);

	UFUNCTION(BlueprintCallable)
	void SpreadResources();

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetNeighbors(int32 Index) const;
};
