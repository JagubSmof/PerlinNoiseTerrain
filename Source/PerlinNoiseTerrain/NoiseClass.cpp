// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseClass.h"

NoiseClass::NoiseClass()
{
	noiseMap = new TArray<float>();
}

NoiseClass::~NoiseClass()
{
	if (noiseMap != nullptr) {
		delete noiseMap;
	}
}

TArray<float>* NoiseClass::GenerateNoiseMap(int mapSize, float scale)
{
	// make sure it isn't dividing by 0 later
	if (scale <= 0)
	{
		scale = 0.0001f;
	}

	noiseMap->SetNum(mapSize * mapSize);

	int vertIndex = 0;
	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			float heightSampleX = x / scale;
			float heightSampleY = y / scale;

			float perlinValue = FMath::PerlinNoise2D(FVector2D(heightSampleX, heightSampleY));

			//perlinValue *= 10.0f;
			(*noiseMap)[vertIndex] = perlinValue * scale;
			vertIndex++;
		}
	}

	return noiseMap;
}