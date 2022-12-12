#include "CParticles.h"
#include "Global.h"
#include "CEventTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystem.h"

ACParticles::ACParticles()
{
	CHelpers::CreateComponent<USceneComponent>( this, &Scene, "Scene" );
	CHelpers::CreateComponent<UTextRenderComponent>( this, &Text, "Text", Scene );

	Text->SetRelativeLocation( FVector( 0, 0, 100 ) );
	Text->SetRelativeRotation( FRotator( 0, 180, 0 ) );
	Text->SetRelativeScale3D( FVector( 2 ) );
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString( GetName() );

	CHelpers::GetAsset<UParticleSystem>( &Particles[0], "ParticleSystem'/Game/Effects/P_Genno_Weapon_Lightning_01.P_Genno_Weapon_Lightning_01'" );
	CHelpers::GetAsset<UParticleSystem>( &Particles[1], "ParticleSystem'/Game/Effects/P_Cube_Mesh_Test.P_Cube_Mesh_Test'" );
	CHelpers::GetAsset<UParticleSystem>( &Particles[2], "ParticleSystem'/Game/Effects/P_HeldCharge_Ice_00.P_HeldCharge_Ice_00'" );
}

void ACParticles::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<ACEventTrigger*> triggers;
	CHelpers::FindActors<ACEventTrigger>( GetWorld(), triggers );
	triggers[0]->OnEventTrigger.AddUFunction( this, "PlayParticle" );
}

void ACParticles::PlayParticle( int32 index )
{
	FTransform transform;
	transform.SetLocation( GetActorLocation() );

	UGameplayStatics::SpawnEmitterAtLocation( GetWorld(), Particles[index], transform );

	CLog::Log( Particles[index] );
}
