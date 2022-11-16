// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawnActor.h"
#include "Components/StaticMeshComponent.h"

//StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'

// Sets default values
ACSpawnActor::ACSpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( "Mesh" );
	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh( L"StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'" );
	if ( mesh.Succeeded() )
	{
		Mesh->SetStaticMesh( mesh.Object );
	}
}

// Called when the game starts or when spawned
void ACSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

