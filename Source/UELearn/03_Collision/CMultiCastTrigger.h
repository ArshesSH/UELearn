#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMultiCastTrigger.generated.h"

// 멀티캐스트 델리게이트 생성
DECLARE_MULTICAST_DELEGATE_TwoParams( FMultiLightBeginOverlap, int32, FLinearColor )

UCLASS()
class UELEARN_API ACMultiCastTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMultiCastTrigger();

protected:
	virtual void BeginPlay() override;

public:
	FMultiLightBeginOverlap OnMultiLightBeginOverlap;
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
};
