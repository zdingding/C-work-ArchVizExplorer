// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/AssetManager.h"
bool UArchGameInstance::AuthenticateUser(const FString& Username, const FString& Password)
{
	bIsLoggedIn = (Username.Equals(ValidUsername) && Password.Equals(ValidPassword));
	return bIsLoggedIn;
}
UArchGameInstance::UArchGameInstance()
{
	
};
bool UArchGameInstance::IsUserLoggedIn() const
{
	return bIsLoggedIn;
}

TArray<FName> UArchGameInstance::GetAvailableLevels() const
{
	return AvailableLevels;
}

void UArchGameInstance::LoadLevel(const FName& LevelName)
{
	if (AvailableLevels.Contains(LevelName))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}
}

void UArchGameInstance::ReturnToMainMenu()
{
	
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuMap");
}

void UArchGameInstance::Init()
{
	Super::Init();
	// 重置登录状态
	bIsLoggedIn = false;
	// 动态加载关卡列表
	LoadLevelsFromFolder("/Game/ArchVizExplorer/Maps");

	// 检查登录状态，如果未登录则跳转到登录关卡
	if (!bIsLoggedIn)
	{
		// 使用定时器确保世界已创建
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Login");
		}, 0.1f, false);
	}
}


void UArchGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UArchGameInstance::LoadLevelsFromFolder(const FString& FolderPath)
{
	AvailableLevels.Empty();

	// 获取资产注册模块
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    
	// 设置过滤器：只获取地图资产
	FARFilter Filter;
	Filter.PackagePaths.Add(*FolderPath);
	Filter.ClassPaths.Add(UWorld::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;

	// 获取所有地图资产
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	// 提取关卡名称
	for (const FAssetData& Asset : AssetData)
	{
		FString AssetName = Asset.AssetName.ToString();
        
		// 排除编辑器专用地图
		if (!AssetName.Contains("_BuiltData") && 
			!AssetName.Contains("_Sub") &&
			!AssetName.Contains("Persistent"))
		{
			AvailableLevels.Add(FName(*AssetName));
		}
	}

	// 确保登录关卡存在
	if (!AvailableLevels.Contains("Login"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Login map not found in %s"), *FolderPath);
	}
}
