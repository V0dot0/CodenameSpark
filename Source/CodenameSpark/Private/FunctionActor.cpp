// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionActor.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFunctionActor::AFunctionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFunctionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFunctionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FHitResult AFunctionActor::TraceFromLocationToLocation(float SpreadShoot)
{
    FHitResult HitResult;

    // Set up the trace parameters
    FCollisionQueryParams TraceParams(FName(TEXT("TraceFromLocationToLocation")), true, this);
    TraceParams.bTraceComplex = true;

    USceneComponent* MySceneComponent = GetPlayerCameraTransform();

    FVector WorldLocation = MySceneComponent->GetComponentLocation();
    FVector TraceStart = WorldLocation;

    FVector ForwardVector = MySceneComponent->GetForwardVector();
    FVector RandomUnitVectorInCone = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(ForwardVector, SpreadShoot);
    FVector TraceEnd = WorldLocation + (RandomUnitVectorInCone * 10000.0f);

    // Perform the trace
    GetWorld()->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECC_Visibility,
        TraceParams
    );

    return HitResult;
}

USceneComponent* AFunctionActor::GetPlayerCameraTransform()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        APlayerCameraManager* PlayerCameraManager = PlayerController->PlayerCameraManager;
        if (PlayerCameraManager)
        {
            USceneComponent* CameraTransform = PlayerCameraManager->GetTransformComponent();
            return CameraTransform;
        }
    }

    return nullptr; 
}