// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

/**
 *  c＋＋でもブループリントでも使えるタグ
 *  シングルトン　（ゲーム上一つしか存在してはいけないクラス）
 */

struct FAuraGameplayTags
{
public:

 static const FAuraGameplayTags& Get(){ return GameplayTags; };
 static void InitializeNativeGameplayTags();

 FGameplayTag Attributes_Secondary_Armor;
 
protected:
 
private:
 static FAuraGameplayTags GameplayTags;
};