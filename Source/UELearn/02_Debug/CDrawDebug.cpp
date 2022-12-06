#include "CDrawDebug.h"
#include "Global.h"

ACDrawDebug::ACDrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	initLocation[0] = FVector::ZeroVector;
	initLocation[1] = FVector( 0, 400, 0 );
	initLocation[2] = FVector( 0, 1000, 0 );
	initLocation[3] = FVector( 0, 1600, 0 );
	initLocation[4] = FVector( 300, 1000, 0 );

	box = FBox( FVector( -50, -100, -50 ), FVector( 50, 100, 50 ) );
	transform.SetLocation( FVector( 200, 1600, 0 ) );
}

void ACDrawDebug::BeginPlay()
{
	Super::BeginPlay();
	for ( int32 i = 0; i < 5; ++i )
	{
		location[i] = initLocation[i] + GetActorLocation();
	}
	DrawDebugBox( GetWorld(), location[0] + box.GetCenter(), box.GetExtent(), FColor::Red, true );
	
}

void ACDrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for ( int32 i = 0; i < 5; ++i )
	{
		location[i] = initLocation[i] + GetActorLocation();
	}

	DrawDebugSolidBox( GetWorld(), location[0] + box.GetCenter(), box.GetExtent(), FColor::Red, true );
	DrawDebugPoint( GetWorld(), location[1], 100, FColor::Red );
	DrawDebugSphere( GetWorld(), location[2], 100, 50, FColor::Green );
	DrawDebugCircle( GetWorld(), location[3], 100, 60, FColor::Blue );
	DrawDebugLine( GetWorld(), location[2], location[3], FColor::Magenta, false, -1,0,4 );

	FVector pos = location[1];
	pos.X += 100;
	pos.Z += 100;
	pos.Y += sin( GetWorld()->GetTimeSeconds() * 3.0f ) * 300.0f;

	DrawDebugPoint( GetWorld(), pos, 100, FColor::Emerald );

	DrawDebugDirectionalArrow( GetWorld(), pos, location[3], 360, FColor::Yellow, false, -1, 0 - 10 );

}


