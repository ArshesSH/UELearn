#include "CAnimNotifyState_Equip.h"
#include "Global.h"
#include "IRifle.h"
#include "CRifle.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}


void UCAnimNotifyState_Equip::NotifyBegin( USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration )
{
	Super::NotifyBegin( MeshComp, Animation, TotalDuration );
	CheckNull( MeshComp );

	IIRifle* rifle = Cast<IIRifle>( MeshComp->GetOwner() );
	CheckNull( rifle );

	rifle->GetRifle()->Begin_Equip();

}

void UCAnimNotifyState_Equip::NotifyEnd( USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation )
{
	Super::NotifyEnd( MeshComp, Animation );
	CheckNull( MeshComp );

	IIRifle* rifle = Cast<IIRifle>( MeshComp->GetOwner() );
	CheckNull( rifle );

	rifle->GetRifle()->End_Equip();
}
