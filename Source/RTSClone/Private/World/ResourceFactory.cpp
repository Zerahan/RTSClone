// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ResourceFactory.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#if WITH_EDITORONLY_DATA
#include "Components/BillboardComponent.h"
#endif

// Sets default values
AResourceFactory::AResourceFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	ColumnOffset = 87.f;
	RowWidth = 50.f;
	MapWidth = 100;
	MapHeight = 100;
	ScaleOverride = FVector::OneVector; //FVector(0.1f, 0.1f, 0.1f);
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
		ExistingResources.Add(-1);
	}
	float Size = 100.f / FMath::Sqrt(3);
	
	HorizontalSpacing = 100.f;
	VerticalSpacing = (3.f/2) * Size;
	HorizontalSpacing *= ScaleOverride.X;
	VerticalSpacing *= ScaleOverride.Y;
}

// Called every frame
void AResourceFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ExistingResources.Num() > 0) {
		CreateInstanceAt(FMath::RandRange(0, MapWidth - 1), FMath::RandRange(0, MapHeight - 1));
	}
}

int32 AResourceFactory::GetIndex(int32 X, int32 Y) const { return Y * MapWidth + X; }
FVector2D AResourceFactory::GetLocation(int32 Index) const { return FVector2D(Index % MapWidth, Index / MapWidth); }
bool AResourceFactory::IsValidLocation(int32 X, int32 Y) const { return ExistingResources.IsValidIndex(GetIndex(X, Y)); }

int32 AResourceFactory::GetInstanceIndexAt(int32 X, int32 Y) const
{
	int32 Index = GetIndex(X, Y);
	if (ExistingResources.IsValidIndex(Index)) return ExistingResources[Index];
	return -2;
}

bool AResourceFactory::CreateInstanceAt(int32 X, int32 Y) {
	if (!IsValid(Mesh)) return false;
	int32 InstanceIndex = GetInstanceIndexAt(X, Y);
	if (InstanceIndex == -2 || InstanceIndex >= 0) return false;
	int32 Index = GetIndex(X, Y);
	FTransform Transform;
	FVector Location = FVector(X * VerticalSpacing, Y * HorizontalSpacing, FMath::RandRange(-90, 90) * ScaleOverride.Z);
	if (X % 2 == 0) Location.Y += (HorizontalSpacing / 2.f);
	Transform.SetLocation(Location);
	//Transform.SetRotation(FRotator(180,0,0).Quaternion());
	Transform.SetScale3D(ScaleOverride);
	ExistingResources[Index] = Mesh->AddInstance(Transform);
	return true;
}

