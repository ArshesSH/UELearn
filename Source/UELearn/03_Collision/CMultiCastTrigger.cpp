#include "CMultiCastTrigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACMultiCastTrigger::ACMultiCastTrigger()
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

void ACMultiCastTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic( this, &ACMultiCastTrigger::ActorBeginOverlap );
	OnActorEndOverlap.AddDynamic( this, &ACMultiCastTrigger::ActorEndOverlap );
	
}

void ACMultiCastTrigger::ActorBeginOverlap( AActor* OverlappedActor, AActor* otherActor )
{
	if ( OnMultiLightBeginOverlap.IsBound() )
	{
		// unreal random은 max 포함
		int32 index = UKismetMathLibrary::RandomIntegerInRange( 0, 2 );
		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange( 0, 1 );
		color.G = UKismetMathLibrary::RandomFloatInRange( 0, 1 );
		color.B = UKismetMathLibrary::RandomFloatInRange( 0, 1 );
		color.A = 1.0f;

		// Multi는 execute 대신 broadcast 사용
		OnMultiLightBeginOverlap.Broadcast(index, color);
	}
}

void ACMultiCastTrigger::ActorEndOverlap( AActor* OverlappedActor, AActor* otherActor )
{
}

