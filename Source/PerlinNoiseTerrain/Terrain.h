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
	~ATerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateMesh();
	class MeshData* GenerateTerrainMesh(TArray<float>* heightMap);

	class UProceduralMeshComponent* mesh;
	class MeshData* meshData;
	class NoiseClass* noiseClass;

	TArray<float>* heightMap;
	TArray<FLinearColor> colourMap;

	// Size of the map. Map will always be square
	const int mapSize = 241;
	
	UPROPERTY(EditAnywhere)
		float mapScale;
	UPROPERTY(EditAnywhere)
		int octaves;
	UPROPERTY(EditAnywhere)
		float persistance;
	UPROPERTY(EditAnywhere)
		float lacunarity;
	UPROPERTY(EditAnywhere)
		float heightMult;

	/* Colour Regions */
	UPROPERTY(EditAnywhere)
		float waterHeight;
	UPROPERTY(EditAnywhere)
		float landHeight = 1;

	/* Material */
	UPROPERTY(EditAnywhere)
		class UMaterial* groundMaterial;
};
