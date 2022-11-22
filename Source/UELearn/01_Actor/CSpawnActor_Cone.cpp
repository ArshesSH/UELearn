#include "CSpawnActor_Cone.h"
#include "Global.h"

ACSpawnActor_Cone::ACSpawnActor_Cone()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>( &mesh, "StaticMesh'/Game/Meshes/Mesh_Cone.Mesh_Cone'" );
	Mesh->SetStaticMesh( mesh );
}
