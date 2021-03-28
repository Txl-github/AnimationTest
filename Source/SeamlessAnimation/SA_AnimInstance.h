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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SA_Animation")
	float MoveDir;

	//轴向移动大小 (X表示前后，Y表示左右)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SA_Animation")
	FVector2D MoveAxis;

	//移动状态 (0表示走，1表示跑)
	float MoveState;

	//世界坐标
	UPROPERTY( BlueprintReadOnly )
	float LeftFootIKOffsetDis;

	UPROPERTY( BlueprintReadOnly )
	float RightFootIKOffsetDis;

	UPROPERTY(BlueprintReadOnly)
	float MeshOffset_Z;

	UPROPERTY(EditAnywhere, Category = "SA_Animation", meta = (UIMin = 0.0f, UIMax = 1.0f))
	float FootIKOffsetDisLerpAlpha = 0.1;

	UPROPERTY(BlueprintReadOnly)
	FRotator LeftFootRotator;

	UPROPERTY(BlueprintReadOnly)
	FRotator RightFootRotator;

public:

	void UpdateDir(ACharacter* ownerCharacter, FVector2D moveAxis);

	void UpdateFootEffectorLoc(float leftFootIKOffsetDis, float rightFootIKOffsetDis);

	void UpdateFootRotate(FHitResult& leftFootHitRet, FHitResult& rightFootHitRet);

protected:
	//float AcceleratedMotion(float DeltaTime);

	FRotator CalculateFootRotate(FHitResult& footHitRet);

};
