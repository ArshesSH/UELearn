#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticles.generated.h"

UCLASS()
class UELEARN_API ACParticles : public AActor
{
	GENERATED_BODY()
	
public:	
	ACParticles();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void PlayParticle( int32 index );

private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;

	// UParticleSystemComponent »ç¿ëÇØµµ µÊ
	UPROPERTY( VisibleDefaultsOnly )
		class UParticleSystem* Particles[3];

};
