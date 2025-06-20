// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DigitalTwinScene.generated.h"

UCLASS()
class DIGITALTWINFRAMEWORK_API ADigitalTwinScene : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADigitalTwinScene();
	// 场景进入确认函数
	UFUNCTION(BlueprintImplementableEvent, Category = "DigitalTwin")
	void OnConfirmEntry();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
