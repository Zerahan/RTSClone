// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ResourceFactory.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#if WITH_EDITORONLY_DATA
#include "Components/BillboardComponent.h"
#include "DrawDebugHelpers.h"
#endif

// Sets default values
AResourceFactory::AResourceFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.TickGroup = ETickingGroup::TG_PostPhysics;

	MapCenter = FVector::ZeroVector;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	OriginPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Origin Point"));
	if (OriginPoint) {
		OriginPoint->SetupAttachment(RootComponent);
		OriginPoint->SetUsingAbsoluteLocation(true);
		OriginPoint->SetWorldLocation(MapCenter);
	}
	
#if WITH_EDITORONLY_DATA
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	if (Billboard) {
		Billboard->SetupAttachment(RootComponent);
		Billboard->SetRelativeLocation(FVector::ZeroVector);
	}
#endif
	
	Mesh = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Mesh Component"));
	if (Mesh) {
		Mesh->SetupAttachment(OriginPoint);
		Mesh->SetRelativeLocation(FVector::ZeroVector);
	}
	TileSize = 100;
	MapWidth = 100;
	MapHeight = 100;
	ScaleOverride = FVector(1, 1, 4); //FVector(0.1f, 0.1f, 0.1f);
	UseHexagonalGrid = true;
	HorizontalSpacing = TileSize;
	VerticalSpacing = TileSize;
}

#if WITH_EDITORONLY_DATA
void AResourceFactory::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property) {
		const FName Name = PropertyChangedEvent.Property->GetFName();
		if (Name == GET_MEMBER_NAME_CHECKED(AResourceFactory, MapCenter)) {
			if(IsValid(OriginPoint)) OriginPoint->SetWorldLocation(MapCenter);
		}
		else if (Name == GET_MEMBER_NAME_CHECKED(AResourceFactory, ScaleOverride)) {
			if (ScaleOverride.X < 0.1f) ScaleOverride.X = 0.1f;
			if (ScaleOverride.Y < 0.1f) ScaleOverride.Y = 0.1f;
			if (ScaleOverride.Z < 0.1f) ScaleOverride.Z = 0.1f;
		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

// Called when the game starts or when spawned
void AResourceFactory::BeginPlay()
{
	Super::BeginPlay();
	ExistingResources.Empty();
	for (int32 i = 0; i < MapWidth * MapHeight; i++) {
		ExistingResources.Add(FResourceDeposit());
	}
	HorizontalSpacing = TileSize;
	if (UseHexagonalGrid) {
		float Size = TileSize / FMath::Sqrt(3);
		VerticalSpacing = (3.f / 2) * Size;
	}
	else {
		VerticalSpacing = TileSize;
	}
	HorizontalSpacing *= ScaleOverride.X;
	VerticalSpacing *= ScaleOverride.Y;
	CreateInstanceAt(0, 0);
	for (int x = -5; x < 5; x++) {
		for (int y = -5; y < 5; y++) {
			//CreateInstanceAt(x, y);
		}
	}
}

// Called every frame
void AResourceFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ExistingResources.Num() > 0) {
		SpreadResources();
	}
}

int32 AResourceFactory::GetIndex(int32 X, int32 Y) const { return FMath::Floor(Y + (MapHeight * 0.5f)) * MapWidth + (X + (MapWidth * 0.5f)); }
FVector2D AResourceFactory::GetLocation(int32 Index) const { return FVector2D(Index % MapWidth, Index / MapWidth); }
FVector2D AResourceFactory::GetLocationWithOffset(int32 Index) const { FVector2D Location = GetLocation(Index); Location.X -= (MapWidth * 0.5f); Location.Y -= (MapHeight * 0.5f); return Location; }
bool AResourceFactory::IsValidLocation(int32 X, int32 Y) const { return ExistingResources.IsValidIndex(GetIndex(X, Y)); }
FVector AResourceFactory::GetWorldLocation(int32 Index, int32 ZOffset) const
{
	FVector2D GridLocation = GetLocationWithOffset(Index);
	FVector WorldLocation = FVector(GridLocation.X, GridLocation.Y, 0);
	WorldLocation.X *= VerticalSpacing;
	WorldLocation.Y *= HorizontalSpacing;
	WorldLocation.Z = ZOffset;
	if (UseHexagonalGrid) {
		if ((int32)GridLocation.X % 2 == 0) WorldLocation.Y += (HorizontalSpacing / 2.f);
	}
	return WorldLocation;
}

int32 AResourceFactory::GetInstanceIndexAt(int32 X, int32 Y) const
{
	int32 Index = GetIndex(X, Y);
	if (ExistingResources.IsValidIndex(Index)) return ExistingResources[Index].InstanceIndex;
	return -2;
}

bool AResourceFactory::CreateInstanceAt(int32 X, int32 Y, uint8 Amount) {
	if (!IsValid(Mesh)) return false;
	int32 InstanceIndex = GetInstanceIndexAt(X, Y);
	if (InstanceIndex == -2 || InstanceIndex >= 0) return false;
	int32 Index = GetIndex(X, Y);
	ExistingResources[Index].MaxAmount = FMath::RandRange(110, 120);
	ExistingResources[Index].Amount = FMath::Clamp(Amount, (uint8)0, ExistingResources[Index].MaxAmount);
	FTransform Transform;
	Transform.SetLocation(GetWorldLocation(Index, ((ExistingResources[Index].Amount / 255.f) * 200 - 110) * ScaleOverride.Z));
	if (FMath::RandBool()) Transform.SetRotation(FRotator(0,180,0).Quaternion());
	Transform.SetScale3D(ScaleOverride);
	ExistingResources[Index].InstanceIndex = Mesh->AddInstance(Transform);
	return true;
}

bool AResourceFactory::SetAmountAt(int32 X, int32 Y, int32 Amount) { return SetAmount(GetIndex(X, Y), Amount); }
bool AResourceFactory::SetAmount(int32 Index, int32 Amount)
{
	if(!ExistingResources.IsValidIndex(Index)) return false;
	if (ExistingResources[Index].InstanceIndex == -1) {
		if (Amount > 0) {
			FVector2D Loc = GetLocationWithOffset(Index);
			CreateInstanceAt((int32)Loc.X, (int32)Loc.Y, Amount);
			return true;
		}
	}
	else {
		uint8 Amt = (uint8)FMath::Clamp(Amount, 0, (int32)ExistingResources[Index].MaxAmount);
		if(Amt == ExistingResources[Index].Amount) return false;
		ExistingResources[Index].Amount = Amt;
		FTransform Transform;
		Mesh->GetInstanceTransform(ExistingResources[Index].InstanceIndex, Transform);
		FVector Loc = Transform.GetLocation();
		Loc.Z = ((ExistingResources[Index].Amount / 255.f) * 200 - 110) * ScaleOverride.Z;
		Transform.SetLocation(Loc);
		Mesh->UpdateInstanceTransform(ExistingResources[Index].InstanceIndex, Transform, false, true);
		return true;
	}
	return false;
}

void AResourceFactory::SpreadResources()
{
	int32 Index = 0;
	TArray<int32> Neighbors;
	TArray<int32> SpreadToList;
	for (int32 x = -(int32)(MapWidth * 0.5); x < (int32)(MapWidth * 0.5); x++) {
		for (int32 y = -(int32)(MapHeight * 0.5); y < (int32)(MapHeight * 0.5); y++) {
			if(FMath::RandBool()) continue;
			Index = GetIndex(x, y);
			if (!ExistingResources.IsValidIndex(Index)) continue;
			if (ExistingResources[Index].InstanceIndex == -1) continue;
			SetAmount(Index, ExistingResources[Index].Amount + FMath::RandRange(0,1));
			if (!ExistingResources[Index].CanSpread) continue;
			if (ExistingResources[Index].Amount > 100) {
				Neighbors = GetNeighbors(Index);
				bool HadValidSpreadTarget = false;
				for (int32 Idx : GetNeighbors(Index)) {
					if (!ExistingResources.IsValidIndex(Idx)) continue;
					if (ExistingResources[Idx].Amount > 0) continue;
					SpreadToList.AddUnique(Idx);
					HadValidSpreadTarget = true;
					if(FMath::RandBool()) ExistingResources[Index].CanSpread = false;
					break;
				}
				if (!HadValidSpreadTarget) {
					ExistingResources[Index].CanSpread = false;
				}
			}
		}
	}
	for (int32 Idx : SpreadToList) {
		//if (FMath::RandRange(0, SpreadToList.Num()) > 0) continue;
		SetAmount(Idx, 1);
	}
	//Mesh->MarkRenderStateDirty();
}

TArray<int32> AResourceFactory::GetNeighbors(int32 Index) const
{
	TArray<int32> Indicies;
	FVector2D OriginLocation = GetLocationWithOffset(Index);
	int32 IndexHolder = -1;
	// Has a world wrap problem...
	if (UseHexagonalGrid) {
		bool UseOffsetTile = (int32)OriginLocation.X % 2 == 0;
		for (int32 x = -1; x < 2; x++) {
			for (int32 y = -1; y < 2; y++) {
				if (x == 0 && y == 0) continue;
				if ( UseOffsetTile && x != 0 && y == -1) continue;
				if (!UseOffsetTile && x != 0 && y == 1) continue;
				IndexHolder = GetIndex(x + OriginLocation.X, y + OriginLocation.Y);
				if (!ExistingResources.IsValidIndex(IndexHolder)) continue;
				Indicies.Add(IndexHolder);
			}
		}
	}
	else {
		for (int32 x = -1; x < 2; x++) {
			for (int32 y = -1; y < 2; y++) {
				if(x == 0 && y == 0) continue;
				IndexHolder = GetIndex(x + OriginLocation.X, y + OriginLocation.Y);
				if(!ExistingResources.IsValidIndex(IndexHolder)) continue;
				Indicies.Add(IndexHolder);
			}
		}
	}
	return Indicies;
}

