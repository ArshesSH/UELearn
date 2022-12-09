#include "CBox.h"
#include "Global.h"
#include "CMultiCastTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACBox::ACBox()
{
	CHelpers::CreateComponent<USceneComponent>( this, &Scene, "Scene" );
	CHelpers::CreateComponent<UTextRenderComponent>( this, &Text, "Text", Scene );

	// Mesh 정보 받아오고 Mesh 생성
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>( &mesh, "StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'" );
	for ( int32 i = 0; i < 3; ++i )
	{
		FString str;
		str.Append( "Mesh_" );
		str.Append( FString::FromInt( i + 1 ) );

		CHelpers::CreateComponent<UStaticMeshComponent>( this, &Mesh[i], FName( str ), Scene );
		Mesh[i]->SetRelativeLocation( FVector( 0, i * 150, 0 ) );
		Mesh[i]->SetStaticMesh( mesh );
		Mesh[i]->SetSimulatePhysics( false );
	}


	Text->SetRelativeLocation( FVector( 0, 0, 100 ) );
	Text->SetRelativeRotation( FRotator( 0, 180, 0 ) );
	Text->SetRelativeScale3D( FVector( 2 ) );
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString( GetName() );


}

void ACBox::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<ACMultiCastTrigger*> triggers;
	CHelpers::FindActors<ACMultiCastTrigger>( GetWorld(), triggers );
	triggers[0]->OnMultiLightBeginOverlap.AddUFunction( this, "OnPhysics" );

	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>( &material, "MaterialInstanceConstant'/Game/Materials/Material_Mesh_Inst.Material_Mesh_Inst'" );

	for ( int32 i = 0; i < 3; ++i )
	{
		Materials[i] = UMaterialInstanceDynamic::Create( material, this );
		Mesh[i]->SetMaterial( 0, Materials[i] );

		FTransform transform = Mesh[i]->GetComponentToWorld();
		WorldLocation[i] = transform.GetLocation();
	}

}

void ACBox::OnPhysics( int32 inIndex, FLinearColor inColor )
{
	for ( int32 i = 0; i < 3; ++i )
	{
		Materials[i]->SetVectorParameterValue( "BaseColor", FLinearColor( 1, 1, 1 ) );
		Mesh[i]->SetSimulatePhysics( false );
		Mesh[i]->SetWorldLocation( WorldLocation[i]);
	}
	Materials[inIndex]->SetVectorParameterValue( "BaseColor", inColor );
	Mesh[inIndex]->SetSimulatePhysics( true );
}

