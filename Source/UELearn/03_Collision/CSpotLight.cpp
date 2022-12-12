#include "CSpotLight.h"
#include "Global.h"
#include "CMultiCastTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/SpotLightComponent.h"

ACSpotLight::ACSpotLight()
{
	CHelpers::CreateComponent<USceneComponent>( this, &Scene, "Scene" );
	CHelpers::CreateComponent<UTextRenderComponent>( this, &Text, "Text", Scene );

	for ( int32 i = 0; i < 3; ++i )
	{
		FString str;
		str.Append( "SpotLight_" );
		str.Append( FString::FromInt( i + 1 ) );

		CHelpers::CreateComponent<USpotLightComponent>( this, &SpotLights[i], FName( str ), Scene );
		SpotLights[i]->SetRelativeLocation( FVector( 0, i * 150, 0 ) );
		SpotLights[i]->SetRelativeRotation( FRotator( -90, 0, 0 ) );
		SpotLights[i]->Intensity = 1e+5f;
		SpotLights[i]->OuterConeAngle = 25.0f;
	}


	Text->SetRelativeLocation( FVector( 0, 0, 100 ) );
	Text->SetRelativeRotation( FRotator( 0, 180, 0 ) );
	Text->SetRelativeScale3D( FVector( 2 ) );
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString( GetName() );
}

void ACSpotLight::BeginPlay()
{
	Super::BeginPlay();

	TArray<ACMultiCastTrigger*> triggers;
	CHelpers::FindActors<ACMultiCastTrigger>( GetWorld(), triggers );
	triggers[0]->OnMultiLightBeginOverlap.AddUFunction( this, "OnLightColor" );
	
}

void ACSpotLight::OnLightColor( int32 inIndex, FLinearColor inColor )
{
	for ( int32 i = 0; i < 3; ++i )
	{
		SpotLights[i]->SetLightColor( FLinearColor(1,1,1) );
	}

	SpotLights[inIndex]->SetLightColor( inColor );
}
