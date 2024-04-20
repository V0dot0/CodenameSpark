// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FunctionActor.generated.h"

UCLASS()
class CODENAMESPARK_API AFunctionActor : public AActor
{
	GENERATED_BODY()
	
	
public:	
	AFunctionActor();
	UFUNCTION(BlueprintCallable, Category = "CameraPlayer")
	USceneComponent*  GetPlayerCameraTransform();

	UFUNCTION(BlueprintCallable, Category = "Trace")
	FHitResult TraceFromLocationToLocation(float SpreadShoot);

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

};
