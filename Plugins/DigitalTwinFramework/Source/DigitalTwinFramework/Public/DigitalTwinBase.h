// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DigitalTwinBase.generated.h"

/**
 * 
 */
UCLASS(Abstract,Blueprintable)
class DIGITALTWINFRAMEWORK_API UDigitalTwinBase : public UObject
{
	GENERATED_BODY()
	public:
	UDigitalTwinBase();
	// 初始化数字孪生系统
UFUNCTION(BlueprintCallable, Category = "DigitalTwin")
	virtual void InitializeDigitalTwin();
	
	// 获取所有场景
	UFUNCTION(BlueprintCallable, Category = "DigitalTwin")
	virtual TArray<FString> GetAvailableScenes() const;
	
	// 进入指定场景
	UFUNCTION(BlueprintCallable, Category = "DigitalTwin")
	virtual void EnterScene(const FString& SceneName);
};
