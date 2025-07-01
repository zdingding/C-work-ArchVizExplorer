// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArchGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARCHVIZEXPLORER_API UArchGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UArchGameInstance();
	// 登录验证
	UFUNCTION(BlueprintCallable, Category = "Authentication")
	bool AuthenticateUser(const FString& Username, const FString& Password);
    
	// 检查登录状态
	UFUNCTION(BlueprintPure, Category = "Authentication")
	bool IsUserLoggedIn() const;
    
	// 获取关卡列表
	UFUNCTION(BlueprintPure, Category = "Levels")
	TArray<FName> GetAvailableLevels() const;
    
	// 加载关卡
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevel(const FName& LevelName);
    
	// 返回主菜单
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void ReturnToMainMenu();
protected:
	virtual void Init() override;
	virtual void Shutdown() override;

private:
	// 硬编码的用户凭证
	const FString ValidUsername = "test123";
	const FString ValidPassword = "test123";
	// 动态加载关卡
	void LoadLevelsFromFolder(const FString& FolderPath);
	// 登录状态
	UPROPERTY(EditAnywhere,Category = "IsLogIn")
	bool bIsLoggedIn = false;
    
	// 关卡列表
	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	TArray<FName> AvailableLevels;	
	
};
