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
    FHitResult HitResult2;
    // объ€вление переменной дл€ хранени€ результатов
    FCollisionQueryParams TraceParams(FName(TEXT("TraceFromLocationToLocation")), true, this); 
    // название в меню Blueprint
    USceneComponent* MySceneComponent = GetPlayerCameraTransform();
    FVector WorldLocation = MySceneComponent->GetComponentLocation();
    FVector TraceStart = WorldLocation;
    // ѕолучение компонентов сцены и координат (например, камеры игрока)
    FVector ForwardVector = MySceneComponent->GetForwardVector();
    // ѕолучение вектора направлени€ вперед дл€ компонента сцены
	FVector RandomUnitVectorInCone = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(ForwardVector, SpreadShoot); 
    // √енераци€ случайного вектора направлени€ внутри конуса с указанным углом разброса (SpreadShoot) от вектора вперед
	FVector TraceEnd = WorldLocation + (RandomUnitVectorInCone * 10000.0f); 
    //  онечна€ точка трассировки вперЄд на рассто€нии 10000 вперЄд, смещЄнна€ конусом с углом разброса.
    TraceParams.bTraceComplex = true;
    TraceParams.AddIgnoredActor(ActorToIgnore);
    // параметры трассировки и добавление объектов, которые нужно игнорировать при трассировке
    GetWorld()->LineTraceSingleByChannel( // ¬ыполнение трассировки
        HitResult,
        TraceStart,
        TraceEnd,
        ECC_Camera,
        TraceParams
    );

    
    FVector TraceStart2 = WeaponBarrelLocation;
    // Ќачальна€ точка второй трассировки устанавливаетс€ на местоположение ствола оружи€
    FVector TraceEnd2 = WorldLocation;
    //  онечна€ точка второй трассировки устанавливаетс€ на местоположение компонента сцены (камеры)
    bool bHitSomething = HitResult.bBlockingHit;
    // ѕроверка, был ли попадание при первой трассировке и сохранение результата в переменную bHitSomething
    if (bHitSomething == true) {
        TraceEnd2 = HitResult.Location + RandomUnitVectorInCone*10.0f;
        // ≈сли был найден блокирующий хит, конечна€ точка второй трассировки устанавливаетс€ на местоположение хита плюс небольшой случайный вектор дл€ смещени€
    }
    else {
        TraceEnd2 = TraceEnd;
        // ≈сли блокирующего хита не было, конечна€ точка второй трассировки устанавливаетс€ на исходную конечную точку первой трассировки
    }
    GetWorld()->LineTraceSingleByChannel(
        HitResult2,
        TraceStart2,
        TraceEnd2,
        ECC_Camera,
        TraceParams
    );
    // ¬ыполнение второй трассировки луча с использованием новой начальной и конечной точек трассировки, параметров трассировки и сохранением результата в HitResult2
    return HitResult2;
    // ¬озвращение результата второй трассировки
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
