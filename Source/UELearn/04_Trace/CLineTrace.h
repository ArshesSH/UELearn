#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

UCLASS()
class UELEARN_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	TArray<class ACCylinder*> Cylinders;

private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;

};
