// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"

#include "IRifle.h"
#include "CRifle.h"

void UCAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    OwnerCharacter = Cast<ACharacter>( TryGetPawnOwner() );
}

void UCAnimInstance::NativeUpdateAnimation( float DeltaSeconds )
{
    Super::NativeUpdateAnimation( DeltaSeconds );

    CheckNull( OwnerCharacter );

    speed = OwnerCharacter->GetVelocity().Size2D();


    //22.12.19 added
    IIRifle* rifle = Cast<IIRifle>( OwnerCharacter );
    if ( !!rifle )
    {
        bEquipped = rifle->GetRifle()->GetEquipped();
    }
}