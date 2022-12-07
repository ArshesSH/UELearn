#include "CComponentOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

ACComponentOverlap::ACComponentOverlap()
{
	CHelpers::CreateComponent<USceneComponent>( this, &Scene, "Scene" );
	CHelpers::CreateComponent<UBoxComponent>( this, &Box, "Box", Scene );
	CHelpers::CreateComponent<UTextRenderComponent>( this, &Text, "Text", Scene );
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Scene);

	Box->SetRelativeScale3D( FVector( 3 ) );
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation( FVector( 0, 0, 100 ) );
	Text->SetRelativeRotation( FRotator( 0, 180, 0 ) );
	Text->SetRelativeScale3D( FVector( 2 ) );
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString( GetName() );

	PointLight->SetLightColor( FLinearColor::Red );

}

void ACComponentOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility( false );

	Box->OnComponentBeginOverlap.AddDynamic( this, &ACComponentOverlap::ComponentBeginOverlap );
	Box->OnComponentEndOverlap.AddDynamic( this, &ACComponentOverlap::ComponentEndOverlap );
}

void ACComponentOverlap::ComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	PointLight->SetVisibility( true );
}

void ACComponentOverlap::ComponentEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	PointLight->SetVisibility( false );
}

