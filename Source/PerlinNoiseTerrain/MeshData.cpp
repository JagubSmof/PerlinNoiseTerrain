// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshData.h"

MeshData::MeshData(int mapSize)
{
	vertices.SetNum(mapSize * mapSize);
	triangles.SetNum((mapSize - 1) * (mapSize - 1) * 6);
	UV0.SetNum(mapSize * mapSize);
	normals.SetNum(mapSize * mapSize);
}

MeshData::~MeshData()
{

}

void MeshData::AddTriangles(int a, int b, int c)
{
	triangles[triangleIndex] = a;
	triangles[triangleIndex + 1] = b;
	triangles[triangleIndex + 2] = c;
	triangleIndex += 3;
}

void MeshData::CreateMesh()
{

}