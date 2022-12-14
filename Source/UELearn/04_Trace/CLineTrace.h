#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FTraceResult, class AActor*, inActor, FLinearColor, inColor );

UCLASS()
class UELEARN_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


protected:
	UFUNCTION( BlueprintCallable )
		void RestoreColor( class ACPlayer* inPlayer );
private:
	UFUNCTION()
		void StartJump( class AActor* inActor, FLinearColor inColor );


private:
	TArray<class ACCylinder*> Cylinders;

public:
	UPROPERTY( BlueprintAssignable )
		FTraceResult OnTraceResult;

private:
	UPROPERTY( VisibleDefaultsOnly )
		class USceneComponent* Scene;
	UPROPERTY( VisibleDefaultsOnly )
		class UTextRenderComponent* Text;

};
