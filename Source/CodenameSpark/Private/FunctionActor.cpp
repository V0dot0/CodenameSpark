// Fill out your copyright notice in the Description page of Project Settings.

#include "FunctionActor.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "CollisionQueryParams.h"

AFunctionActor::AFunctionActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFunctionActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFunctionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FHitResult AFunctionActor::TraceFromLocationToLocation(float SpreadShoot, FVector WeaponBarrelLocation, AActor* ActorToIgnore)
{
    FHitResult HitResult;
   
    FCollisionQueryParams TraceParams(FName(TEXT("TraceFromLocationToLocation")), true, this);
    TraceParams.bTraceComplex = true;

    TraceParams.AddIgnoredActor(ActorToIgnore);

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
        ECC_Camera,
        TraceParams
    );

    FHitResult HitResult2;
    FVector TraceStart2 = WeaponBarrelLocation;
    FVector TraceEnd2 = WorldLocation;
    bool bHitSomething = HitResult.bBlockingHit;

    if (bHitSomething == true) {
        TraceEnd2 = HitResult.Location + RandomUnitVectorInCone*10.0f;
    }
    else {
        TraceEnd2 = TraceEnd;
    }

    GetWorld()->LineTraceSingleByChannel(
        HitResult2,
        TraceStart2,
        TraceEnd2,
        ECC_Camera,
        TraceParams
    );

    return HitResult2;
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
