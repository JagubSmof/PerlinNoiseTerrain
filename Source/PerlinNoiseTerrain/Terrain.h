// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Terrain.generated.h"

UCLASS()
class PERLINNOISETERRAIN_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateMesh();
	MeshData* GenerateTerrainMesh(TArray<int> heightMap);

	class UProceduralMeshComponent* mesh;
	class MeshData* meshData;

	UPROPERTY(EditAnywhere)
		// Size of the map. Map will always be square
		int mapSize;
	UPROPERTY(EditAnywhere)
		float mapScale;
};
