#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "COverride.generated.h"

UCLASS()
class UELEARN_API ACOverride : public AActor
{
	GENERATED_BODY()
	
public:	
	ACOverride();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION( BlueprintImplementableEvent )
		void ChangeColorRed();
	UFUNCTION( BlueprintNativeEvent )
		void ChangeColorWhite();
		void ChangeColorWhite_Implementation();
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
