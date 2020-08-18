// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessTerrain.h"

// Sets default values
AEndlessTerrain::AEndlessTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEndlessTerrain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndlessTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector viewerPosV3 = viewer->GetActorLocation();

	viewerPos = FVector2D(viewerPosV3.X, viewerPosV3.Z);
	UpdateVisibleChunks();
}

void AEndlessTerrain::UpdateVisibleChunks()
{
	for (size_t i = 0; i < (&terrainChunksVisibleLastUpdate)->Num(); i++)
	{
		terrainChunksVisibleLastUpdate[i]->SetVisible(false);
	}

	terrainChunksVisibleLastUpdate.Empty();

	int currentChunkCoordX = FMath::RoundToInt(viewerPos.X / chunkSize);
	int currentChunkCoordY = FMath::RoundToInt(viewerPos.Y / chunkSize);

	for (int yOffset = -chunksVisibleInViewDist; yOffset <= chunksVisibleInViewDist;
		yOffset++)
	{
		for (int xOffset = -chunksVisibleInViewDist; xOffset <= chunksVisibleInViewDist;
			xOffset++)
		{
			FVector2D viewedChunkCoord = FVector2D(currentChunkCoordX + xOffset, currentChunkCoordY + yOffset);
			if (dictTerrainChunk.Contains(viewedChunkCoord))
			{
				dictTerrainChunk[viewedChunkCoord]->UpdateTerrainChunk();
				if (dictTerrainChunk[viewedChunkCoord]->IsVisible())
				{
					terrainChunksVisibleLastUpdate.Add(dictTerrainChunk[viewedChunkCoord]);
				}
			}
			else
			{
				dictTerrainChunk.Add(viewedChunkCoord, new TerrainChunk(viewedChunkCoord, chunkSize));
			}
		}
	}
}



//////////////////////
/*	Terrain Chunk	*/
//////////////////////

TerrainChunk::TerrainChunk(FVector2D coord, int size)
{
	chunkPos = coord * size;
	FVector posV3 = FVector(chunkPos.X, 0, chunkPos.Y);

	endlessTerrain->AMeshActor->SetActorLocation(posV3);
	endlessTerrain->AMeshActor->SetActorRelativeScale3D(FVector(1, 1, 1) * size);
	SetVisible(false);
}

TerrainChunk::~TerrainChunk()
{
	if (endlessTerrain != nullptr)
	{
		delete endlessTerrain;
	}
}

void TerrainChunk::UpdateTerrainChunk()
{
	// calc distance of vectors
	float sqrDist = FVector2D::Distance(chunkPos, endlessTerrain->viewerPos) * FVector2D::Distance(chunkPos, endlessTerrain->viewerPos);
	float viewerDistFromNearestEdge = FMath::Sqrt(sqrDist);
	bool isChunkVisible = (viewerDistFromNearestEdge <= endlessTerrain->maxViewDist);
	SetVisible(isChunkVisible);
}

void TerrainChunk::SetVisible(bool isChunkVisible)
{
	// if actor is visible, it shouldn't be hidden
	endlessTerrain->AMeshActor->SetActorHiddenInGame(!isChunkVisible);
}

bool TerrainChunk::IsVisible()
{
	// if actor is hidden, it shouldn't be visible
	return !endlessTerrain->AMeshActor->IsHidden();
}
