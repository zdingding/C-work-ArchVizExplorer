// Fill out your copyright notice in the Description page of Project Settings.


#include "DigitalTwinManager.h"
#include "Engine/World.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelScriptActor.h"
#include "Misc/Paths.h"

UDigitalTwinManager::UDigitalTwinManager()
{
	
}

void UDigitalTwinManager::InitializeDigitalTwin()
{
	Super::InitializeDigitalTwin();
	LoadSceneConfiguration();
}

TArray<FString> UDigitalTwinManager::GetAvailableScenes() const
{
	return Super::GetAvailableScenes();
	TArray<FString> SceneNames;
	SceneMap.GetKeys(SceneNames);
	return SceneNames;
}

void UDigitalTwinManager::EnterScene(const FString& SceneName)
{
	Super::EnterScene(SceneName);
	if(SceneMap.Contains(SceneName))
	{
		FString MapPath = *SceneMap.Find(SceneName);
		UE_LOG(LogTemp, Log, TEXT("Entering scene: %s"), *MapPath);
		// 实际加载场景的代码
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Scene not found: %s"), *SceneName);
	}
}

void UDigitalTwinManager::LoadSceneConfiguration()
{
	// 清空现有场景
	SceneMap.Empty();
	// 定义场景根路径
	const FString SceneRootPath = "/Game/ArchVizExplorer/Maps/";

	// 获取所有地图资产（实际项目中应从配置文件读取）
	SceneMap.Add("FactoryFloor", SceneRootPath + "Factory_Floor");
	SceneMap.Add("Warehouse", SceneRootPath + "Warehouse");
	SceneMap.Add("ControlRoom", SceneRootPath + "Control_Room");
	SceneMap.Add("OutdoorArea", SceneRootPath + "Outdoor_Area");
	
}

void UDigitalTwinManager::CallLevelBlueprintConfirm(FString MapPath)
{
	// 查找当前世界的所有关卡
	UWorld* World = GetWorld();
	if (!World) return;

	for (ULevel* Level : World->GetLevels())
	{
		if (Level && Level->GetOuter()->GetName() == MapPath)
		{
			ALevelScriptActor* LevelScript = Level->GetLevelScriptActor();
			if (LevelScript)
			{
				// 使用反射调用确认函数
				UFunction* ConfirmFunction = LevelScript->FindFunction(FName("ConfirmEntry"));
				if (ConfirmFunction)
				{
					LevelScript->ProcessEvent(ConfirmFunction, nullptr);
					UE_LOG(LogTemp, Log, TEXT("Called ConfirmEntry on %s"), *MapPath);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("ConfirmEntry function not found in %s"), *MapPath);
				}
			}
		}
	}
}
