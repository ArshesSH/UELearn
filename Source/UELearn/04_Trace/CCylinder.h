#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCylinder.generated.h"

UCLASS()
class UELEARN_API ACCylinder : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCylinder();

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;
	UPROPERTY( VisibleDefaultsOnly )
		class UStaticMeshComponent* Mesh;

};
