#include "CCube.h"

#include "Global.h"
#include "Components/StaticMeshComponent.h"

ACCube::ACCube()
{
	CHelpers::CreateComponent<UStaticMeshComponent>( this, &Mesh, "Mesh" );

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>( &mesh, "StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'" );
	Mesh->SetStaticMesh( mesh );
	Mesh->SetSimulatePhysics( true );
	Mesh->SetCollisionObjectType( ECollisionChannel::ECC_PhysicsBody );
}

void ACCube::BeginPlay()
{
	Super::BeginPlay();
	
}
