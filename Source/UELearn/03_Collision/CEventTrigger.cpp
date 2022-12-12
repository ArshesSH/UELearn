#include "CEventTrigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACEventTrigger::ACEventTrigger()
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

void ACEventTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic( this, &ACEventTrigger::ActorBeginOverlap );
}

void ACEventTrigger::ActorBeginOverlap( AActor* OverlappedActor, AActor* otherActor )
{
	if ( OnEventTrigger.IsBound() )
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange( 0, 2 );
		OnEventTrigger.Broadcast(index);
	}
}
