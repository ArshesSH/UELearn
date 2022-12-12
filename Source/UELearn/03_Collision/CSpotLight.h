#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpotLight.generated.h"

UCLASS()
class UELEARN_API ACSpotLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpotLight();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnLightColor( int32 inIndex, FLinearColor inColor );

private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;
	UPROPERTY( VisibleDefaultsOnly )
		class USpotLightComponent* SpotLights[3];
};
