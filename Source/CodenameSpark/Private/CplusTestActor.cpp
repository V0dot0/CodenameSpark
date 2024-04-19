// Fill out your copyright notice in the Description page of Project Settings.


#include "CplusTestActor.h"

// Sets default values
ACplusTestActor::ACplusTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	num = 4;
	num2 = 4.4;
	myName = FName(TEXT("NAMEEEE"));
}

// Called when the game starts or when spawned
void ACplusTestActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Example text that prints a float:")));

}

// Called every frame
void ACplusTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

