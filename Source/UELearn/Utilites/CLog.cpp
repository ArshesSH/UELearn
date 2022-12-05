#include "CLog.h"

#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC( GameObject, Warning, All)


void CLog::Print( int32 inValue, int32 inKey, float duration, FColor inColor )
{
	GEngine->AddOnScreenDebugMessage( inKey, duration, inColor, FString::FromInt( inValue ) );
}

void CLog::Print( float inValue, int32 inKey, float duration, FColor inColor )
{
	GEngine->AddOnScreenDebugMessage( inKey, duration, inColor, FString::SanitizeFloat( inValue ) );
}

void CLog::Print( const FString& inValue, int32 inKey, float duration, FColor inColor )
{
	GEngine->AddOnScreenDebugMessage( inKey, duration, inColor, inValue );
}

void CLog::Print( const FVector& inValue, int32 inKey, float duration, FColor inColor )
{
	GEngine->AddOnScreenDebugMessage( inKey, duration, inColor, inValue.ToString() );
}

void CLog::Print( const FRotator& inValue, int32 inKey, float duration, FColor inColor )
{
	GEngine->AddOnScreenDebugMessage( inKey, duration, inColor, inValue.ToString() );
}

void CLog::Log( int32 inValue )
{
	//UE_LOG( LogTemp, Display, L"%d", inValue );
	UE_LOG( GameObject, Warning, L"%d", inValue )
}

void CLog::Log( float inValue )
{
	UE_LOG( GameObject, Warning, L"%f", inValue )
}

void CLog::Log( const FString& inValue )
{
	UE_LOG( GameObject, Warning, L"%s", *inValue )
}

void CLog::Log( const FVector& inValue )
{
	UE_LOG( GameObject, Warning, L"%s", *inValue.ToString() )
}

void CLog::Log( const FRotator& inValue )
{
	UE_LOG( GameObject, Warning, L"%s", *inValue.ToString() )
}

void CLog::Log( const UObject* inObject )
{
	FString str;
	if ( !!inObject )
	{
		str.Append( inObject->GetName() );
	}
	str.Append( !!inObject ? "Not Null" : "Null" );

	UE_LOG( GameObject, Warning, L"%s", *str );
}

void CLog::Log( const FString& inFuncName, int32 inLineNumber )
{
	FString str;
	str.Append( inFuncName );
	str.Append( ", " );
	str.Append( FString::FromInt( inLineNumber ) );

	UE_LOG( GameObject, Warning, L"%s", *str );
}
