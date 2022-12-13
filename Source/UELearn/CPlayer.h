#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class UELEARN_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION( BlueprintCallable )
		void ChangeColor( FLinearColor inColor );

private:
	void OnMoveForward( float axis );
	void OnMoveRight( float axis );
	void OnHorizontalLook( float axis );
	void OnVerticalLook( float axis );
	void OnRunning();
	void OffRuning();

private:
	UPROPERTY( VisibleDefaultsOnly )
	class USpringArmComponent* SpringArm;
	UPROPERTY( VisibleDefaultsOnly )
	class UCameraComponent* Camera;
	UPROPERTY( EditAnywhere )
	bool bInverseVerticalCamera = false;


	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;
};
