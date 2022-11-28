#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawner.generated.h"

UCLASS()
class UELEARN_API ACSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpawner();

protected:
	virtual void BeginPlay() override;

private:
	// 스폰 대상
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class ACSpawnActor> spawnClass[3];

	// 생성한 인스턴스들
	class ACSpawnActor* spawnActors[3];


};
