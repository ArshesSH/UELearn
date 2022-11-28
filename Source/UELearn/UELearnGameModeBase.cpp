#include "UELearnGameModeBase.h"
#include "Global.h"

AUELearnGameModeBase::AUELearnGameModeBase()
{
	/*
	// 블루프린트는 레퍼런스 뒤에 _C 붙여줘야함
	ConstructorHelpers::FClassFinder<APawn> pawn( L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'" );
	if ( pawn.Succeeded() )
	{
		pawn.Class = ~~~
	}
	*/

	CHelpers::GetClass<APawn>( &DefaultPawnClass, L"Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'" );

}
