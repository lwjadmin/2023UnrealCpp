// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim_ThirdPersonCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE4CPP_API UAnim_ThirdPersonCharacter : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_ThirdPersonCharacter();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	float MoveSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool bIsInAir = false;
	
};
