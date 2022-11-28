#include "CSpawner.h"
#include "Global.h"
#include "CSpawnActor.h"

ACSpawner::ACSpawner()
{
}

void ACSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	for ( int32 i = 0; i < 3; ++i )
	{
		FTransform transform;
		FVector location = GetActorLocation();
			
		//spawnActors[i] = GetWorld()->SpawnActor<ACSpawnActor>( spawnClass[i], transform );
		//spawnActors[i]->SetActorLocation( FVector( location.X, location.Y + i * 400, location.Z ) );

		transform.SetLocation( FVector( location.X, location.Y + i * 400, location.Z ) );
		spawnActors[i] = GetWorld()->SpawnActor<ACSpawnActor>( spawnClass[i], transform );
	}
}
