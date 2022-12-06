#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDrawDebug.generated.h"

UCLASS()
class UELEARN_API ACDrawDebug : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDrawDebug();

protected:
	virtual void BeginPlay() override;

public:	 
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY( EditAnywhere, Category = "DrawDebug" )
		FVector initLocation[5];
	UPROPERTY( EditAnywhere, Category = "DrawDebug" )
		FBox box;
	UPROPERTY( EditAnywhere, Category = "DrawDebug" )
		FTransform transform;

	FVector location[5];

};
