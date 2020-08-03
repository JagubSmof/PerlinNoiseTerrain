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

	TArray<float>* noiseMap;

	TArray<float>* GenerateNoiseMap(int mapSize, float scale, int octaves, float persistance, float lacunarity);

	TArray<FVector> vertices;
	TArray<int> triangles;
	TArray<FVector2D> UV0;
	//TArray<FVector> normals;
};
