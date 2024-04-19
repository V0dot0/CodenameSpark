// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CplusTestActor.generated.h"

UCLASS()
class CODENAMESPARK_API ACplusTestActor : public AActor
{
	GENERATED_BODY()

	int16 num;
	float num2;
	FName myName;
	
public:	
	// Sets default values for this actor's properties
	ACplusTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
