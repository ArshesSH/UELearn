#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTrigger.generated.h"

DECLARE_DELEGATE( FBoxLightBeginOverlap );
DECLARE_DELEGATE( FBoxLightEndOverlap );

UCLASS()
class UELEARN_API ACTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap( AActor* OverlappedActor, AActor* otherActor );
	UFUNCTION()
		void ActorEndOverlap( AActor* OverlappedActor, AActor* otherActor );

private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UBoxComponent* Box;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;

public:
	FBoxLightBeginOverlap OnBoxLightBeginOverlap;
	FBoxLightEndOverlap OnBoxLightEndOverlap;
};
