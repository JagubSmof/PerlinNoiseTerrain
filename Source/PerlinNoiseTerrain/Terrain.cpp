// Fill out your copyright notice in the Description page of Project Settings.

#include "Terrain.h"
#include "MeshData.h"
#include "NoiseClass.h"
#include "ProceduralMeshComponent.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	meshData = new MeshData(mapSize);
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
	TArray<int> heightMap = NoiseClass::GenerateNoiseMap(mapSize, mapScale);

	GenerateTerrainMesh(heightMap);

	mesh->CreateMeshSection_LinearColor(0, meshData->vertices, meshData->triangles, meshData->normals,
		meshData->UV0, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
}

MeshData* ATerrain::GenerateTerrainMesh(TArray<int> heightMap)
{
	int heightMapSize = heightMap.Num();

	// for centering the mesh
	float topLeftX = (heightMapSize - 1) / -2.0f;
	float topLeftZ = (heightMapSize - 1) / 2.0f;

	int vertIndex = 0;

	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			meshData->vertices[vertIndex] = FVector(topLeftX + x, heightMap[vertIndex],
				topLeftZ + y);
			meshData->UV0[vertIndex] = FVector2D(x / float(mapSize), y / float(mapSize));

			if (x < mapSize - 1 && y < mapSize - 1)
			{
				meshData->AddTriangles(vertIndex, vertIndex + mapSize + 1,
					vertIndex + mapSize);
				meshData->AddTriangles(vertIndex + mapSize + 1, vertIndex, vertIndex + 1);
			}
			vertIndex++;
		}
	}
	return meshData;
}