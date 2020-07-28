// Fill out your copyright notice in the Description page of Project Settings.

#include "Terrain.h"
#include "NoiseClass.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	noise = new NoiseClass();
}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	
	CreateMesh();
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerrain::CreateMesh()
{
	TArray<int> heightMap = noise->GenerateNoiseMap(mapWidth, mapHeight, mapScale);

	mesh->CreateMeshSection_LinearColor(0, TArray<FVector>(), TArray<int>(), TArray<FVector>(),
		TArray<FVector2D>(), TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
}