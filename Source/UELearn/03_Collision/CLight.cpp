#include "CLight.h"
#include "Global.h"
#include "CTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

ACLight::ACLight()
{
	CHelpers::CreateComponent<USceneComponent>( this, &Scene, "Scene" );
	CHelpers::CreateComponent<UTextRenderComponent>( this, &Text, "Text", Scene );
	CHelpers::CreateComponent<UPointLightComponent>( this, &PointLight, "PointLight", Scene );

	Text->SetRelativeLocation( FVector( 0, 0, 100 ) );
	Text->SetRelativeRotation( FRotator( 0, 180, 0 ) );
	Text->SetRelativeScale3D( FVector( 2 ) );
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString( GetName() );

	PointLight->Intensity = 1e+4f;
	PointLight->AttenuationRadius = 200;	// 감쇠 범위
	PointLight->LightColor = FColor( 255, 128, 5 );
}

void ACLight::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility( false );

	// T SubClass들은 StaticClass를 상속받는 클래스
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass( GetWorld(), ACTrigger::StaticClass(), actors );
	CheckFalse( actors.Num() > 0 );
	ACTrigger* trigger = Cast<ACTrigger>( actors[0] );
	trigger->OnBoxLightBeginOverlap.BindUFunction( this, "OnLight" );
	trigger->OnBoxLightEndOverlap.BindUFunction( this, "OffLight" );
}

void ACLight::OnLight()
{
	PointLight->SetVisibility( true );
}

void ACLight::OffLight()
{
	PointLight->SetVisibility( false );
}

