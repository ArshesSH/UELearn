#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLight.generated.h"

UCLASS()
class UELEARN_API ACLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLight();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnLight();
	UFUNCTION()
		void OffLight();
	UFUNCTION()
		FString OnRandomLight( FLinearColor inColor );

private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;
	UPROPERTY( VisibleDefaultsOnly )
		class UPointLightComponent* PointLight;
	UPROPERTY( VisibleDefaultsOnly )
		class UPointLightComponent* PointLight2;

};
