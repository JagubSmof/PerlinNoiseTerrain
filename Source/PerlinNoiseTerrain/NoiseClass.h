// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PERLINNOISETERRAIN_API NoiseClass
{
public:
	NoiseClass();
	~NoiseClass();

	static TArray<int> GenerateNoiseMap(int mapSize, float scale);

	TArray<FVector> vertices;
	TArray<int> triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> normals;
};
