#pragma once

#include "CoreMinimal.h"

#define PrintLine(){CLog::Log( __FUNCTION__, __LINE__);}

class UELEARN_API CLog
{
public:
	// Print to Screen
	static void Print( int32 inValue, int32 inKey = -1, float duration = 10.0f, FColor inColor = FColor::Blue );
	static void Print( float inValue, int32 inKey = -1, float duration = 10.0f, FColor inColor = FColor::Blue );
	static void Print( const FString& inValue, int32 inKey = -1, float duration = 10.0f, FColor inColor = FColor::Blue );
	static void Print( const FVector& inValue, int32 inKey = -1, float duration = 10.0f, FColor inColor = FColor::Blue );
	static void Print( const FRotator& inValue, int32 inKey = -1, float duration = 10.0f, FColor inColor = FColor::Blue );

	// Logging
	static void Log( int32 inValue );
	static void Log( float inValue );
	static void Log( const FString& inValue );
	static void Log( const FVector& inValue );
	static void Log( const FRotator& inValue );

	static void Log( const UObject* inObject );
	static void Log( const FString& inFuncName, int32 inLineNumber );
};
