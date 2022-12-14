#include "CSweepTrigger.h"

#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "CExplosion.h"

ACSweepTrigger::ACSweepTrigger()
{
	CHelpers::CreateComponent<USceneComponent>( this, &Scene, "Scene" );
	CHelpers::CreateComponent<UBoxComponent>( this, &Box, "Box", Scene );
	CHelpers::CreateComponent<UTextRenderComponent>( this, &Text, "Text", Scene );

	Box->SetRelativeScale3D( FVector( 3 ) );
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation( FVector( 0, 0, 100 ) );
	Text->SetRelativeRotation( FRotator( 0, 180, 0 ) );
	Text->SetRelativeScale3D( FVector( 2 ) );
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString( GetName() );


}

void ACSweepTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<ACExplosion*> explosions;
	CHelpers::FindActors( GetWorld(), explosions );

	OnActorBeginOverlap.AddDynamic( explosions[0], &ACExplosion::ActorBeginOverlap );
}