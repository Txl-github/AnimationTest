// Fill out your copyright notice in the Description page of Project Settings.


#include "SA_AnimInstance.h"
#include "SeamlessAnimationCharacter.h"


void USA_AnimInstance::UpdateDir(ACharacter* ownerCharacter, FVector2D moveAxis)
{

	//FString debugString1 = FString::Printf(TEXT("X=%f, Y=%f"), moveAxis.X, moveAxis.Y);
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, debugString1);

	MoveAxis = moveAxis;

	/*
	//方向向量乘以方向长度，移动左右
	FVector vec1 = ownerCharacter->GetActorForwardVector() * MoveAxis.X;
	FVector vec2 = ownerCharacter->GetActorRightVector() * MoveAxis.Y;
	FVector velocity = vec1 + vec2;

	//计算抬头
	velocity.Z = ownerCharacter->GetControlRotation().Yaw;
	
	//FString debugString2 = FString::Printf(TEXT("X=%f, Y=%f, Z=%f"), velocity.X, velocity.Y, velocity.Z);
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, debugString2);

	//计算移动方向
	MoveDir = CalculateDirection(velocity, ownerCharacter->GetActorRotation());
	*/
}

void USA_AnimInstance::UpdateFootEffectorLoc(float leftFootIKOffsetDis, float rightFootIKOffsetDis)
{
	float goalMeshOffset_Z = 0;

	//防止脚部在下楼梯时被角色碰撞体限制导致悬空，这里把 mesh往下移、脚部IK距离差值往上移 解决这个问题
	if (leftFootIKOffsetDis <= rightFootIKOffsetDis)
	{
		goalMeshOffset_Z = leftFootIKOffsetDis;
		rightFootIKOffsetDis = rightFootIKOffsetDis + FMath::Abs(leftFootIKOffsetDis);
		leftFootIKOffsetDis = 0;
	}
	else
	{
		goalMeshOffset_Z = rightFootIKOffsetDis;
		leftFootIKOffsetDis = leftFootIKOffsetDis + FMath::Abs(rightFootIKOffsetDis);
		rightFootIKOffsetDis = 0;
	}

	//向目标位置平滑过渡
	LeftFootIKOffsetDis = FMath::Lerp(LeftFootIKOffsetDis, leftFootIKOffsetDis, FootIKOffsetDisLerpAlpha);
	RightFootIKOffsetDis = FMath::Lerp(RightFootIKOffsetDis, rightFootIKOffsetDis, FootIKOffsetDisLerpAlpha);
	MeshOffset_Z = FMath::Lerp(MeshOffset_Z, goalMeshOffset_Z, FootIKOffsetDisLerpAlpha);

}

void USA_AnimInstance::UpdateFootRotate(FHitResult& leftFootHitRet, FHitResult& rightFootHitRet)
{
	LeftFootRotator = CalculateFootRotate(leftFootHitRet);

	RightFootRotator = CalculateFootRotate(rightFootHitRet);
}

FRotator USA_AnimInstance::CalculateFootRotate(FHitResult& footHitRet)
{
	//得到脚所踩平面的法线
	FVector impactNormal = footHitRet.ImpactNormal;
	//计算平面和脚部的弧度
	float roll = FMath::Atan2(impactNormal.Y, impactNormal.Z);
	float pitch = FMath::Atan2(impactNormal.X, impactNormal.Z);

	//怪不得一直没有效果，旋转是用角度计算的，上面算出来的是弧度!!!!!!
	return FRotator(FMath::RadiansToDegrees(pitch), 0.0f, FMath::RadiansToDegrees(roll));
}




