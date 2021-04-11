// Fill out your copyright notice in the Description page of Project Settings.


#include "Pendulum.h"
#include "Components/StaticMeshComponent.h"
#include "QuaternionRotation.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>

// Sets default values
APendulum::APendulum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CircularComp = CreateDefaultSubobject<UStaticMeshComponent>("CircularComp");
	RootComponent = CircularComp;
	StickComp = CreateDefaultSubobject<UStaticMeshComponent>("StickComp");
	StickComp->AttachToComponent(CircularComp, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APendulum::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APendulum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SQua q = FQuaternion::MakeRotatorQuaternion(FVector(0, 0, 1), PI/60);

	FVector eV = FQuaternion::QuaternionRotation(q, FVector(1, 0, 0));//局部坐标系下，X轴是物体的前方
	FRotator r = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, eV);
	StickComp->AddRelativeRotation(r);
	//FString debugStr_two = FString::Printf(TEXT("My: X=%f Y=%f Z=%f"), eV.X, eV.Y, eV.Z);
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, debugStr_two);
	
	//FQuat qq(q.X, q.Y, q.Z, q.W);
	//StickComp->AddRelativeRotation(qq);
	//StickComp->AddWorldRotation(qq);
}

