// Fill out your copyright notice in the Description page of Project Settings.


#include "CplusTestActor.h"
#include "Kismet/KismetMathLibrary.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACplusTestActor::ACplusTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	num = 4;
	num2 = 4.4;
	myName = FName(TEXT("NAMEEEE"));
}



// Called every frame
void ACplusTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    GetWorldTimerManager().SetTimer(TimerHandle_UpdateVariable, this, &ACplusTestActor::MyFunctionToUpdateVariable, 2.0f, true);
}

// Called when the game starts or when spawned
void ACplusTestActor::BeginPlay()
{
    UWorld* World = GetWorldFromActor(this);
    //UWorld* ActorWorld = this->GetWorld();
	//UWorld* ActorWorld = GetWorldFromActor(this);
    ActorWorld = World;
}

UWorld* ACplusTestActor::GetWorldFromActor(AActor* Actor)
{
    if (Actor)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("WORKS!!!!")));
        return Actor->GetWorld();
    }
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("BREAKSS!")));
    return nullptr;
}

void ACplusTestActor::MyFunctionToUpdateVariable()
{
    UWorld* World = GetWorldFromActor(this);
    ActorWorld = World;
}

FHitResult ACplusTestActor::PerformLineTrace3(USceneComponent* MySceneComponent, float SpreadShoot)
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

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Camera, TraceParams);
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, 2.0f);



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
