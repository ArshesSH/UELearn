// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty01.generated.h"

UCLASS()
class UELEARN_API ACProperty01 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACProperty01();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY( EditAnywhere )
		int A = 10;
	UPROPERTY( EditInstanceOnly )
		int B = 20;
	UPROPERTY( EditDefaultsOnly )
		int C;
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
		int D = 40;


};
