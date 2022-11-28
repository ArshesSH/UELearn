// Fill out your copyright notice in the Description page of Project Settings.


#include "CSpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

//StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'
// MaterialInstanceConstant'/Game/Materials/Material_Mesh_Inst.Material_Mesh_Inst'

// Sets default values
ACSpawnActor::ACSpawnActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>( "Mesh" );
	RootComponent = Mesh;

	/*
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh( L"StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'" );
	if ( mesh.Succeeded() )
	{
		Mesh->SetStaticMesh( mesh.Object );
	}
	*/
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>( &mesh, "StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'" );
	Mesh->SetStaticMesh( mesh );

}

// Called when the game starts or when spawned
void ACSpawnActor::BeginPlay()
{
	Super::BeginPlay();	
	
	//UObject* obj = StaticLoadObject( UMaterialInstanceConstant::StaticClass(), nullptr,
	//	L"MaterialInstanceConstant'/Game/Materials/Material_Mesh_Inst.Material_Mesh_Inst'" );

	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>( obj );

	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>( &material,
		"MaterialInstanceConstant'/Game/Materials/Material_Mesh_Inst.Material_Mesh_Inst'" );
	Material = UMaterialInstanceDynamic::Create( material, this );
	Mesh->SetMaterial( 0, Material );

	// 타이머 설정
	UKismetSystemLibrary::K2_SetTimer( this, "ChangeColor", 1.0f, true);

}

void ACSpawnActor::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange( 0, 1 );
	color.G = UKismetMathLibrary::RandomFloatInRange( 0, 1 );
	color.B = UKismetMathLibrary::RandomFloatInRange( 0, 1 );
	color.A = 1.0f;

	Material->SetVectorParameterValue( "BaseColor", color );
}

