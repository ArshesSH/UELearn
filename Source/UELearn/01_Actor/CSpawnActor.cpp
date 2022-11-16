// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawnActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACSpawnActor::ACSpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( "Mesh" );
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ACSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

