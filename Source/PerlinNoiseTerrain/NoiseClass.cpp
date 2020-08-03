// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseClass.h"
#include "Kismet/KismetMathLibrary.h"

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

TArray<float>* NoiseClass::GenerateNoiseMap(int mapSize, float scale, int octaves, float persistance, float lacunarity)
{
	// make sure it isn't dividing by 0 later
	if (scale <= 0)
	{
		scale = 0.0001f;
	}

	noiseMap->SetNum(mapSize * mapSize);

	float maxNoiseHeight = 0;
	float minNoiseHeight = 0;

	int vertIndex = 0;
	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			float amplitude = 1.0f;
			float frequency = 1.0f;
			float noiseHeight = 0.0f;
			for (int i = 0; i < octaves; i++)
			{
				float heightSampleX = x / scale * frequency;
				float heightSampleY = y / scale * frequency;

				float perlinValue = FMath::PerlinNoise2D(FVector2D(heightSampleX, heightSampleY)) * 2 - 1;

				noiseHeight += perlinValue * scale * amplitude;
				amplitude *= persistance;
				frequency *= lacunarity;

				if (maxNoiseHeight < noiseHeight)
				{
					maxNoiseHeight = noiseHeight;
				}
				else if (minNoiseHeight > noiseHeight)
				{
					minNoiseHeight = noiseHeight;
				}

				//perlinValue *= 10.0f;
				(*noiseMap)[vertIndex] = noiseHeight;
				vertIndex++;
			}
		}
	}

	for (int i = 0; i < mapSize; i++)
	{
		(*noiseMap)[i] = UKismetMathLibrary::NormalizeToRange(minNoiseHeight, maxNoiseHeight, (*noiseMap)[i]);
	}

	return noiseMap;
}