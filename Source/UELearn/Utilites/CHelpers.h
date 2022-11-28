#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

class UELEARN_API CHelpers
{
public:
	template<typename T> static void GetAsset( T** outObject, FString inPath )
	{
		ConstructorHelpers::FObjectFinder<T> asset( *inPath );
		verifyf( asset.Succeeded(), L"asset.Succeeded()" );
		*outObject = asset.Object;
	}
	template<typename T> static void GetAssetDynamic( T** outObject, FString inPath )
	{
		T* obj = Cast<T>(StaticLoadObject( T::StaticClass(), NULL, *inPath ));

		// !!obj => obj != nullptr
		verifyf( !!obj, L"!!asset" );
		*outObject = obj;
	}
	// � ���Ϳ��� � ������Ʈ�� � �̸����� ��� �θ�� �ΰ� ��������
	template<typename T> static void CreateComponent( AActor* inActor, T** inComponent, FName inName, USceneComponent* inParent = nullptr )
	{
		*inComponent = inActor->CreateDefaultSubobject<T>( inName );
		if ( !!inParent )
		{
			(*inComponent)->SetupAttachment( inParent );
			return;
		}

		inActor->SetRootComponent( *inComponent );
	}
	template<typename T> static void GetClass( TSubclassOf<T>* outClass, FString inPath )
	{
		ConstructorHelpers::FClassFinder<T> asset( *inPath );
		verifyf( asset.Succeeded(), L"asset.Succeeded()" );
		*outClass = asset.Class;
	}
};