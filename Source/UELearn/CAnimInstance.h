// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UELEARN_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category = "Animation" )
		float speed;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

private:
	class ACharacter* OwnerCharacter;
};
