#include "UELearnGameModeBase.h"
#include "Global.h"

AUELearnGameModeBase::AUELearnGameModeBase()
{
	/*
	// �������Ʈ�� ���۷��� �ڿ� _C �ٿ������
	ConstructorHelpers::FClassFinder<APawn> pawn( L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'" );
	if ( pawn.Succeeded() )
	{
		pawn.Class = ~~~
	}
	*/

	CHelpers::GetClass<APawn>( &DefaultPawnClass, L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'" );

}
