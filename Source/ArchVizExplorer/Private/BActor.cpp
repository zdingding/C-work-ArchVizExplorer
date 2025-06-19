// Fill out your copyright notice in the Description page of Project Settings.


#include "BActor.h"

// Sets default values
ABActor::ABActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

