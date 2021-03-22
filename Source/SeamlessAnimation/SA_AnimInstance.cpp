// Fill out your copyright notice in the Description page of Project Settings.


#include "SA_AnimInstance.h"
#include "SeamlessAnimationCharacter.h"


void USA_AnimInstance::UpdateDir(ACharacter* ownerCharacter, FVector2D moveAxis)
{

	FString debugString1 = FString::Printf(TEXT("X=%f, Y=%f"), moveAxis.X, moveAxis.Y);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, debugString1);

	MoveAxis = moveAxis;

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
}

