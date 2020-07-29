// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseClass.h"

NoiseClass::NoiseClass()
{
}

NoiseClass::~NoiseClass()
{
}

TArray<int> NoiseClass::GenerateNoiseMap(int mapSize, float scale)
{
	// make sure it isn't dividing by 0 later
	if (scale <= 0)
	{
		scale = 0.0001f;
	}

	TArray<int> noiseMap;
	noiseMap.SetNum(mapSize * mapSize);

	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			int vertIndex = 0;
			float heightSampleX = x / scale;
			float heightSampleY = y / scale;

			float perlinValue = FMath::PerlinNoise2D(FVector2D(heightSampleX, heightSampleY));
			noiseMap[vertIndex] = perlinValue;
			vertIndex++;
		}
	}
	return noiseMap;
}