// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PerlinNoiseTerrainGameMode.h"
#include "PerlinNoiseTerrainPawn.h"

APerlinNoiseTerrainGameMode::APerlinNoiseTerrainGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = APerlinNoiseTerrainPawn::StaticClass();
}
