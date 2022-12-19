#include "CAnimNotifyState_Unequip.h"
#include "Global.h"
#include "IRifle.h"
#include "CRifle.h"

FString UCAnimNotifyState_Unequip::GetNotifyName_Implementation() const
{
	return "Unequip";
}


void UCAnimNotifyState_Unequip::NotifyBegin( USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration )
{
	Super::NotifyBegin( MeshComp, Animation, TotalDuration );
	CheckNull( MeshComp );

	IIRifle* rifle = Cast<IIRifle>( MeshComp->GetOwner() );
	CheckNull( rifle );

	rifle->GetRifle()->Begin_Unequip();


}

void UCAnimNotifyState_Unequip::NotifyEnd( USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation )
{
	Super::NotifyEnd( MeshComp, Animation );
	CheckNull( MeshComp );

	IIRifle* rifle = Cast<IIRifle>( MeshComp->GetOwner() );
	CheckNull( rifle );

	rifle->GetRifle()->End_Unequip();
}