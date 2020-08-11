// Fill out your copyright notice in the Description page of Project Settings.

#include "Terrain.h"
#include "Engine.h"
#include "MeshData.h"
#include "NoiseClass.h"
#include "ProceduralMeshComponent.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	material = CreateDefaultSubobject<UMaterial>(TEXT("Material"));
}

ATerrain::~ATerrain() {
}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	meshData = new MeshData(mapSize);
	noiseClass = new NoiseClass();
	CreateMesh();
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATerrain::CreateMesh()
{
	heightMap = noiseClass->GenerateNoiseMap(mapSize, mapScale, octaves, persistance, lacunarity);

	for (int i = 0; i < mapSize; i++)
	{
		colourMap.SetNum(mapSize * mapSize);
		float currentHeight = (*heightMap)[i];
	}

	meshData = GenerateTerrainMesh(heightMap);
	mesh->CreateMeshSection_LinearColor(0, meshData->vertices, meshData->triangles, TArray<FVector>(),
		meshData->UV0, colourMap, TArray<FProcMeshTangent>(), true);

	mesh->SetMaterial(0, material);
}

MeshData* ATerrain::GenerateTerrainMesh(TArray<float>* noiseMap)
{
	int heightMapSize = noiseMap->Num();

	int vertIndex = 0;

	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			meshData->vertices[vertIndex] = FVector(x, (*noiseMap)[vertIndex] * heightMult, y);
			meshData->UV0[vertIndex] = FVector2D((x / float(mapSize)) * 10, (y / float(mapSize)) * 10);

			if (x < mapSize - 1 && y < mapSize - 1)
			{
				meshData->AddTriangles(vertIndex, vertIndex + mapSize + 1, vertIndex + mapSize);
				meshData->AddTriangles(vertIndex + mapSize + 1, vertIndex, vertIndex + 1);
			}
			vertIndex++;
		}
	}

	return meshData;
}
