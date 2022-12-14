#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSweepTrigger.generated.h"

UCLASS()
class UELEARN_API ACSweepTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSweepTrigger();

protected:
	virtual void BeginPlay() override;


	// >> : 22.12.14 Added
private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UBoxComponent* Box;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;
	// <<
};
