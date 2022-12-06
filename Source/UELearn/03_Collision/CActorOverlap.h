#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActorOverlap.generated.h"

UCLASS()
class UELEARN_API ACActorOverlap : public AActor
{
	GENERATED_BODY()
	
public:	
	ACActorOverlap();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap( AActor* OverlappedActor, AActor* otherActor );
	UFFUNCTION()
		void ActorEndOverlap( AActor* OverlappedActor, AActor* otherActor );

private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UBoxComponent* Box;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;


};
