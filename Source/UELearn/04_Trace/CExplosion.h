#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CExplosion.generated.h"

UCLASS()
class UELEARN_API ACExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	ACExplosion();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void ActorBeginOverlap( AActor* OverlappedActor, AActor* OtherActor );

private:
	UPROPERTY( VisibleDefaultsOnly )
		class UParticleSystemComponent* Particle;
};
