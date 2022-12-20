#include "CRifle.h"

#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "CPlayer.h"
#include "Animation/AnimMontage.h"

ACRifle::ACRifle()
{
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
