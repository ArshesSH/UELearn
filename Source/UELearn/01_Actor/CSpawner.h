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
	// ���� ���
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class ACSpawnActor> spawnClass[3];

	// ������ �ν��Ͻ���
	class ACSpawnActor* spawnActors[3];


};
