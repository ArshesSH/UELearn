#include "COverride.h"

#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "CPlayer.h"

ACOverride::ACOverride()
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

void ACOverride::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic( this, &ACOverride::ActorBeginOverlap );
	OnActorEndOverlap.AddDynamic( this, &ACOverride::ActorEndOverlap );
	
}

void ACOverride::ChangeColorWhite_Implementation()
{
	ACPlayer* player = Cast<ACPlayer>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );
	player->ChangeColor( FLinearColor(0,0,1) );
}

void ACOverride::ActorBeginOverlap( AActor* OverlappedActor, AActor* otherActor )
{
	ChangeColorRed();
}

void ACOverride::ActorEndOverlap( AActor* OverlappedActor, AActor* otherActor )
{
	ChangeColorWhite();
}

