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

	AMeshActor->SetActorLocation(posV3);
	AMeshActor->SetActorRelativeScale3D(FVector(1, 1, 1) * size);
	SetVisible(false);
}

TerrainChunk::~TerrainChunk()
{
}

void TerrainChunk::UpdateTerrainChunk()
{
	// calc distance of vectors
	FVector2D::Distance(chunkPos, endlessTerrain->viewerPos);
	//float viewerDistFromNearestEdge = FMath::Sqrt(bounds.sqrDistance(viewerpos));
	//bool isChunkVisible = (viewerDistFromNearestEdge <= AEndlessTerrain::maxViewDist);
	//SetVisible(isChunkVisible);
}

void TerrainChunk::SetVisible(bool isChunkVisible)
{
}

bool TerrainChunk::IsVisible()
{
	return false;
}
