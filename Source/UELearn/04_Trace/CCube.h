#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCube.generated.h"

UCLASS()
class UELEARN_API ACCube : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCube();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY( VisibleDefaultsOnly )
		class UStaticMeshComponent* Mesh;
};
