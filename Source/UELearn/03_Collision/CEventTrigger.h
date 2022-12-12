#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEventTrigger.generated.h"

UCLASS()
class UELEARN_API ACEventTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Event delegate »ý¼º
	DECLARE_EVENT_OneParam( ACEventTrigger, FEventTrigger, int32 )
	
public:	
	ACEventTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap( AActor* OverlappedActor, AActor* otherActor );
	
public:
	FEventTrigger OnEventTrigger;
private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UBoxComponent* Box;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;
};
