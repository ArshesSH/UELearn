#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IRifle.h"
#include "CPlayer.generated.h"

UCLASS()
class UELEARN_API ACPlayer : public ACharacter, public IIRifle
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

	FORCEINLINE class ACRifle* GetRifle() override { return Rifle; }

protected:
	UFUNCTION( BlueprintImplementableEvent )
		void OnZoomIn();
	UFUNCTION( BlueprintImplementableEvent )
		void OnZoomOut();

private:
	void OnMoveForward( float axis );
	void OnMoveRight( float axis );
	void OnHorizontalLook( float axis );
	void OnVerticalLook( float axis );
	void OnRunning();
	void OffRuning();
	void OnRifle();
	void OnAim();
	void OffAim();

protected:
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly )
		class USpringArmComponent* SpringArm;
	UPROPERTY( BlueprintReadOnly, VisibleDefaultsOnly )
		class UCameraComponent* Camera;

private:
	UPROPERTY( EditAnywhere )
	bool bInverseVerticalCamera = false;

	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	//  22.12.16 added for rifle
	class ACRifle* Rifle;
};
