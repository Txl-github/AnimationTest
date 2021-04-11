// Fill out your copyright notice in the Description page of Project Settings.


#include "QuaternionRotation.h"

SQua FQuaternion::MakeRotatorQuaternion(FVector axisOfRotation, float angle)
{
	//单位化
	axisOfRotation.Normalize();
	//创造四元数
	SQua q;
	float halfAngle = angle / 2;
	q.X = axisOfRotation.X * FMath::Sin(halfAngle);
	q.Y = axisOfRotation.Y * FMath::Sin(halfAngle);
	q.Z = axisOfRotation.Z * FMath::Sin(halfAngle);
	q.W = FMath::Cos(halfAngle);
	return q;
}

SQua FQuaternion::QuaternionMultiplication(SQua leftQua, SQua rightQua)
{
	FVector leftV(leftQua.X, leftQua.Y, leftQua.Z);
	float leftS = leftQua.W;
	FVector rightV(rightQua.X, rightQua.Y, rightQua.Z);
	float rightS = rightQua.W;

	FVector qV = leftS * rightV + rightS * leftV + FVector::CrossProduct(leftV, rightV);
	float qS = leftS * rightS - FVector::DotProduct(leftV, rightV);

	return SQua(qV.X, qV.Y, qV.Z, qS);
}

FVector FQuaternion::QuaternionRotation(SQua q, FVector v)
{
	SQua qC(-q.X, -q.Y, -q.Z, q.W);
	SQua originV(v.X, v.Y, v.Z, 0);

	//四元数旋转公式 rV = qVq*
	SQua  qTemp1= QuaternionMultiplication(q, originV);
	SQua qTemp2 = QuaternionMultiplication(qTemp1, qC);

	//返回旋转后的向量
	return FVector(qTemp2.X, qTemp2.Y, qTemp2.Z);
}
