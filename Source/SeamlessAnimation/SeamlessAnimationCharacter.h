// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SeamlessAnimationCharacter.generated.h"


UCLASS(config=Game)
class ASeamlessAnimationCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ASeamlessAnimationCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	//角色是否为跟运动
	bool bRootMotion = true;

	bool bMoveAccelerate = false;

	UPROPERTY(EditAnywhere, Category = "SA_Animation", meta = (UIMin=0.001f, UIMax=0.1f))
	float AnimBlendMinValue = 0.02f;

	//轴向移动大小 (X表示前后，Y表示左右),用于跟动画
	FVector2D MoveAxis;

	UPROPERTY(EditAnywhere, Category = "SA_Animation", meta = (UIMin = 0.3f, UIMax = 0.7f))
	float IKLineTraceStartScale_Z = 0.5;

	UPROPERTY(EditAnywhere, Category = "SA_Animation", meta = (UIMin = 0.3f, UIMax = 0.7f))
	float IKLineTraceEndScale_Z = 0.5;

	class USA_AnimInstance* AnimInstance;

public:
	virtual void BeginPlay() override;

protected:

	//返回碰撞距离
	UFUNCTION(BlueprintCallable, Category = "SA_Animation")
	float IKLineTrace(FName boneName, FHitResult& OutHitResult);

	virtual void Tick(float DeltaTime) override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void MoveAccelerate(float Value);

	float MoveAxisValueBlend(float axisValue, float inputValue);


	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

