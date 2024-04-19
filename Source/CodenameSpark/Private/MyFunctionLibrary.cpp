// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

FString UMyFunctionLibrary::super(FString Name)
{
	return FString();
}

FRotator UMyFunctionLibrary::SwayCalculate(float InterpSpeed, float SwayPlus, float SwayMinus, float MouseX, float MouseY, FRotator Rwrist, float deltaTime)
{
	float WristRoll = Rwrist.Roll;
	float WristPitch = Rwrist.Pitch;
	float WristYaw = Rwrist.Yaw;
	float MapRollWrist = UKismetMathLibrary::MapRangeClamped(MouseY, -1, 1, SwayPlus, SwayMinus);
	float MapYawWrist = UKismetMathLibrary::MapRangeClamped(MouseX, -1, 1, SwayMinus, SwayPlus);

	return FRotator(UKismetMathLibrary::FInterpTo(WristPitch, 0, deltaTime, InterpSpeed), UKismetMathLibrary::FInterpTo(WristYaw, MapYawWrist, deltaTime, InterpSpeed), UKismetMathLibrary::FInterpTo(WristRoll, MapRollWrist, deltaTime, InterpSpeed));

}

