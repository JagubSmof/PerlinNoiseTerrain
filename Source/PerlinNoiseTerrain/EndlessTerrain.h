// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessTerrain.generated.h"

UCLASS()
class PERLINNOISETERRAIN_API AEndlessTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndlessTerrain();

	float maxViewDist = 300;

	UPROPERTY(EditAnywhere)
		class AActor* viewer;

	FVector2D viewerPos;

	TMap<FVector2D, class TerrainChunk*> dictTerrainChunk;
	TArray<class TerrainChunk*> terrainChunksVisibleLastUpdate;
private:
	int chunkSize;
	int chunksVisibleInViewDist;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateVisibleChunks();
};


//////////////////////

/*	Terrain Chunk	*/

//////////////////////

class PERLINNOISETERRAIN_API TerrainChunk
{
public:
	AActor* AMeshActor;
	FVector2D chunkPos;
	AEndlessTerrain* endlessTerrain;

	TerrainChunk(FVector2D coord, int size);
	~TerrainChunk();
	void UpdateTerrainChunk();
	void SetVisible(bool isChunkVisible);
	bool IsVisible();
};