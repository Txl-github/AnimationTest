// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SA_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SEAMLESSANIMATION_API USA_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()


protected:
	//移动方向(-180,180)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SA_RootMotion")
	float MoveDir;

	//轴向移动大小 (X表示前后，Y表示左右)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SA_RootMotion")
	FVector2D MoveAxis;

	//移动状态 (0表示走，1表示跑)
	float MoveState;

public:

	void UpdateDir(ACharacter* ownerCharacter, FVector2D moveAxis);

};
