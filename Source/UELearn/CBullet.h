#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

UCLASS()
class UELEARN_API ACBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBullet();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			const FHitResult& Hit );


private:
	UPROPERTY( VisibleDefaultsOnly )
		class UStaticMeshComponent* Mesh;
	UPROPERTY( VisibleDefaultsOnly )
		class UProjectileMovementComponent* Projectile;


};
