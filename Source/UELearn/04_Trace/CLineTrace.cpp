#include "CLineTrace.h"

#include "Global.h"
#include "CCylinder.h"
#include "Components/TextRenderComponent.h"

ACLineTrace::ACLineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>( this, &Scene, "Scene" );
	CHelpers::CreateComponent<UTextRenderComponent>( this, &Text, "Text", Scene );


	Text->SetRelativeLocation( FVector( 0, 0, 100 ) );
	Text->SetRelativeRotation( FRotator( 0, 180, 0 ) );
	Text->SetRelativeScale3D( FVector( 2 ) );
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString( GetName() );
}

void ACLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	CHelpers::FindActors<ACCylinder>( GetWorld(), Cylinders );
}

void ACLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( Cylinders.Num() < 2 )
	{
		return;
	}

	FVector start = Cylinders[0]->GetActorLocation();
	FVector end = Cylinders[1]->GetActorLocation();

	start.Z -= 10;
	end.Z -= 10;
	DrawDebugLine( GetWorld(), start, end, FColor::Yellow, false );



	start.Z += 10;
	end.Z += 10;

	// �Ǹ��� ��ü�� �ݶ��̴��� ������ ��� ����
	TArray<AActor*> ignoreActors;
	ignoreActors.Add( Cylinders[0] );
	ignoreActors.Add( Cylinders[1] );

	FHitResult hitResult;
	if ( UKismetSystemLibrary::LineTraceSingleByProfile( GetWorld(), start, end, "Pawn", false, ignoreActors,
		EDrawDebugTrace::ForOneFrame, hitResult, true, FLinearColor::Green, FLinearColor::Red ) )
	{
		CLog::Log( hitResult.GetActor()->GetName() );
	}
}

