// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PERLINNOISETERRAIN_API MeshData
{
public:
	MeshData(int mapSize);
	~MeshData();
	void AddTriangles(int a, int b, int c);
	void CreateMesh();

	TArray<FVector> vertices;
	TArray<int> triangles;
	TArray<FVector2D> UV0;
	//TArray<FVector> normals;

private:
	int triangleIndex = 0;
};
