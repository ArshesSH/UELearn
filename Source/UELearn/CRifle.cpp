#include "CRifle.h"

#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "CPlayer.h"
#include "Animation/AnimMontage.h"
#include "Engine/StaticMeshActor.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USkeletalMeshComponent>( this, &Mesh, "Mesh" );

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>( &mesh, "SkeletalMesh'/Game/Weapons/Meshes/AR4/SK_AR4.SK_AR4'" );
	Mesh->SetSkeletalMesh( mesh );

	CHelpers::GetAsset<UAnimMontage>( &GrabMontage, "AnimMontage'/Game/Character/Montages/Rifle_Grab_Montage.Rifle_Grab_Montage'" );
	CHelpers::GetAsset<UAnimMontage>( &UnGrabMontage, "AnimMontage'/Game/Character/Montages/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'" );
}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>( GetOwner() );
	AttachToComponent( OwnerCharacter->GetMesh(), FAttachmentTransformRules( EAttachmentRule::KeepRelative, true ), HolsterSocket);

}

void ACRifle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	CheckFalse( bAiming );

	IIRifle* rifle = Cast<IIRifle>( OwnerCharacter );
	CheckNull( rifle );

	FVector start, end, direction;
	rifle->GetLocationAndDirection( start, end, direction );

	//DrawDebugLine( GetWorld(), start, end, FColor::Green, false, 3.0f );

	FCollisionQueryParams params;
	params.AddIgnoredActor( this );
	params.AddIgnoredActor( OwnerCharacter );

	FHitResult hitResult;
	if ( GetWorld()->LineTraceSingleByChannel( hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params ) )
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>( hitResult.GetActor() );
		if(!!staticMeshActor )
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>( staticMeshActor->GetRootComponent() );
			if ( !!meshComponent )
			{
				if ( meshComponent->BodyInstance.bSimulatePhysics )
				{
					// to do something

					rifle->OnFocus();
					return;
				}
			}
		}
	}
	rifle->OffFocus();
}

ACRifle* ACRifle::Spawn( UWorld* inWorld, ACharacter* inOwner )
{
	FActorSpawnParameters params;
	params.Owner = inOwner;

	return inWorld->SpawnActor<ACRifle>( params );
}

void ACRifle::Equip()
{
	CheckTrue( bEquipped );
	CheckTrue( bEquipping );

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage( GrabMontage );
}

void ACRifle::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent( OwnerCharacter->GetMesh(), FAttachmentTransformRules( EAttachmentRule::KeepRelative, true ), HandSocket );
}

void ACRifle::End_Equip()
{
	bEquipping = false;
}

void ACRifle::Unequip()
{
	CheckFalse( bEquipped );
	CheckTrue( bEquipping );

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage( UnGrabMontage );
}

void ACRifle::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent( OwnerCharacter->GetMesh(), FAttachmentTransformRules( EAttachmentRule::KeepRelative, true ), HolsterSocket );
}

void ACRifle::End_Unequip()
{
	bEquipping = false;
}

void ACRifle::Begin_Aiming()
{
	bAiming = true;
}

void ACRifle::End_Aiming()
{
	bAiming = false;
}

void ACRifle::Begin_Fire()
{
	CheckFalse( bEquipped );
	CheckTrue( bEquipping );
	CheckFalse( bAiming );
	CheckTrue( bFiring );

	Firing();
}

void ACRifle::Firing()
{
	bFiring = true;

	IIRifle* rifle = Cast<IIRifle>( OwnerCharacter );
	CheckNull( rifle );

	FVector start, end, direction;
	rifle->GetLocationAndDirection( start, end, direction );

	FCollisionQueryParams params;
	params.AddIgnoredActor( this );
	params.AddIgnoredActor( OwnerCharacter );

	FHitResult hitResult;
	if ( GetWorld()->LineTraceSingleByChannel( hitResult, start, end, ECollisionChannel::ECC_WorldDynamic, params ) )
	{
		AStaticMeshActor* staticMeshActor = Cast<AStaticMeshActor>( hitResult.GetActor() );
		if ( !!staticMeshActor )
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>( staticMeshActor->GetRootComponent() );
			if ( !!meshComponent )
			{
				if ( meshComponent->BodyInstance.bSimulatePhysics )
				{
					// to do something

					direction = staticMeshActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
					direction.Normalize();

					meshComponent->AddImpulseAtLocation( direction * meshComponent->GetMass() * 100, OwnerCharacter->GetActorLocation() );

					return;
				}
			}
		}
	}

}

void ACRifle::End_Fire()
{
	bFiring = false;
}
