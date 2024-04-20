// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/EngineTypes.h"

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

FHitResult UMyFunctionLibrary::PerformLineTrace(const UObject* WorldContextObject, FVector Start, FVector End)
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	if (WorldContextObject)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
		if (World)
		{
			World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		}
	}
	return FHitResult();
}


FHitResult UMyFunctionLibrary::PerformLineTrace2(UWorld* World, AActor* Actor1,  USceneComponent* MySceneComponent, float SpreadShoot)
{
	FVector WorldLocation = MySceneComponent->GetComponentLocation();
    FVector TraceStart = WorldLocation;

	FVector ForwardVector = MySceneComponent->GetForwardVector();
	FVector RandomUnitVectorInCone = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(ForwardVector, SpreadShoot);
	FVector TraceEnd = WorldLocation + (RandomUnitVectorInCone * 10000.0f);

	FHitResult HitResult;

	//bool bHit = LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility); 
	//bool LineTraceSingleByChannel
	//(
	//	struct FHitResult& HitResult,
	//	const FVector & TraceStart,
	//	const FVector & TraceEnd,
	//	ECollisionChannel TraceChannel,
	//	const FCollisionQueryParams & Params,
	//	const FCollisionResponseParams & ResponseParam
	//);
	

	// Perform the line trace
	FCollisionQueryParams TraceParams;

	bool bHit = World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Camera, TraceParams);
	//DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, 2.0f);



    //FHitResult HitResult;
    //FCollisionQueryParams QueryParams;
    //QueryParams.AddIgnoredActor(PlayerController->GetPawn()); // Ignore the player pawn

    //bool bHit = LineTraceSingleByChannel(HitResult, TraceStart, TracePreEnd, ECC_Visibility, QueryParams);
    //if (bHit)
    //{
    //    OutHitLocation = HitResult.Location;
    //    OutHitNormal = HitResult.Normal;
    //}

    return HitResult;
}
