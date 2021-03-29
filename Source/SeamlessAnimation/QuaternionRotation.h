// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct SQua
{
    SQua()
        :X(0), Y(0), Z(0), W(0)
    {};
    SQua(float x, float y, float z, float w)
        :X(x), Y(y), Z(z), W(w)
    {};

    float X;
    float Y;
    float Z;
    float W;
};

/**
 * 
 */
class SEAMLESSANIMATION_API FQuaternion
{
public:
    //根据旋转轴和旋转角度制作一个旋转单位四元数
    static SQua MakeRotatorQuaternion(FVector axisOfRotation, float angle);

    //四元数乘法
    static SQua QuaternionMultiplication(SQua leftQua, SQua rightQua);

    //四元数旋转
    static FVector QuaternionRotation(SQua q, FVector v);
};
