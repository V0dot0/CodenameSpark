// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CODENAMESPARK_API UMyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "PrintCopy")
		static FString super(FString Name);

		UFUNCTION(BlueprintCallable, Category = "SetStats")
		static FRotator SwayCalculate(float InterpSpeed, float SwayPlus, float SwayMinus, float MouseX, float MouseY, FRotator Rwrist, float deltaTime);
		//static FString text(FString Name);
		//static FFloat16 10.f;
		
		UFUNCTION(BlueprintCallable, Category = "LineTrace", meta = (WorldContext = "WorldContextObject"))
		static FHitResult PerformLineTrace(const UObject* WorldContextObject, FVector Start, FVector End);

		UFUNCTION(BlueprintCallable, Category = "LineTrace")
		static FHitResult PerformLineTrace2(UWorld* World, USceneComponent* MySceneComponent,float SpreadShoot);

};
