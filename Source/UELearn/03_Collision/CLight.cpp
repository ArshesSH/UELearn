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
	CHelpers::CreateComponent<UPointLightComponent>( this, &PointLight2, "PointLight2", Scene );

	Text->SetRelativeLocation( FVector( 0, 0, 100 ) );
	Text->SetRelativeRotation( FRotator( 0, 180, 0 ) );
	Text->SetRelativeScale3D( FVector( 2 ) );
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString( GetName() );

	PointLight->Intensity = 1e+4f;
	PointLight->AttenuationRadius = 200;	// 감쇠 범위
	PointLight->LightColor = FColor( 255, 128, 5 );

	PointLight2->SetRelativeLocation( FVector( 0, 400, 0 ) );
	PointLight2->Intensity = 1e+4f;
	PointLight2->AttenuationRadius = 200;
	PointLight2->LightColor = FColor( 255, 255, 0 );
}

void ACLight::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetVisibility( false );
	PointLight2->SetVisibility( false );

	// T SubClass들은 StaticClass를 상속받는 클래스
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass( GetWorld(), ACTrigger::StaticClass(), actors );
	CheckFalse( actors.Num() > 0 );
	ACTrigger* trigger = Cast<ACTrigger>( actors[0] );
	trigger->OnBoxLightBeginOverlap.BindUFunction( this, "OnLight" );
	trigger->OnBoxLightEndOverlap.BindUFunction( this, "OffLight" );

	trigger->OnBoxLightRandomBeginOverlap.BindUFunction( this, "OnRandomLight" );
}

void ACLight::OnLight()
{
	PointLight->SetVisibility( true );
}

void ACLight::OffLight()
{
	PointLight->SetVisibility( false );
	PointLight2->SetVisibility( false );
}

FString ACLight::OnRandomLight( FLinearColor inColor )
{
	PointLight2->SetVisibility( true );
	PointLight2->SetLightColor( inColor );
	return inColor.ToString();
}

