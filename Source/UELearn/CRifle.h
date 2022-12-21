#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRifle.generated.h"

UCLASS()
class UELEARN_API ACRifle : public AActor
{
	GENERATED_BODY()

public:	
	ACRifle();

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;

public:
	static ACRifle* Spawn( class UWorld* inWorld, class ACharacter* inOwner );

	FORCEINLINE bool GetEquipped() { return bEquipped; }
	FORCEINLINE bool GetEquipping() { return bEquipping; }
	FORCEINLINE bool GetAiming() { return bAiming; }
	
	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Begin_Aiming();
	void End_Aiming();
	
	void Begin_Fire();
	void Firing();
	void End_Fire();

private:
	UPROPERTY( VisibleDefaultsOnly, Category = "Rifle" )
		class USkeletalMeshComponent* Mesh;
	UPROPERTY( VisibleDefaultsOnly, Category = "Rifle" )
		FName HandSocket = "Hand_Rifle";
	UPROPERTY( VisibleDefaultsOnly, Category = "Rifle" )
		FName HolsterSocket = "Holster_Rifle";


	UPROPERTY( VisibleDefaultsOnly, Category = "Rifle" )
		class UAnimMontage* GrabMontage;
	UPROPERTY( VisibleDefaultsOnly, Category = "Rifle" )
		class UAnimMontage* UnGrabMontage;

	class  ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;
	bool bFiring;
};
