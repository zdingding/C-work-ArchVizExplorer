// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DigitalTwinBase.h"
#include "DigitalTwinManager.generated.h"

/**
 * 
 */
UCLASS()
class DIGITALTWINFRAMEWORK_API UDigitalTwinManager : public UDigitalTwinBase
{
	GENERATED_BODY()
public:
	UDigitalTwinManager();
	virtual void InitializeDigitalTwin() override;
	virtual TArray<FString> GetAvailableScenes() const override;
	virtual void EnterScene(const FString& SceneName) override;

protected:
	// 场景数据
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DigitalTwin")
	TMap<FString, FString> SceneMap; // <场景名, 地图路径>

	// 加载场景配置
	void LoadSceneConfiguration();

	// 使用反射调用关卡蓝图的确认函数
	void CallLevelBlueprintConfirm(FString MapPath);	
};
