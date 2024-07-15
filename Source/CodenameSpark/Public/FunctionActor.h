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

	// ѕосле компил€ции кода, функци€ TraceFromLocationToLocation станет доступной дл€ использовани€ в Blueprints использу€ BlueprintCallable
	UFUNCTION(BlueprintCallable, Category = "Trace") 
	FHitResult TraceFromLocationToLocation(float SpreadShoot, FVector WeaponBarrelLocation, AActor* ActorToIgnore);

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

};
