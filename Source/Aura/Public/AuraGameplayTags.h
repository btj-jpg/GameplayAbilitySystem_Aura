// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

/**
 *  タグをネイティブタグに登録するためのクラス
 *  メリット c++でもタグを使える、処理が最適化されている
 *  c＋＋でもブループリントでも使えるタグ
 *  シングルトン　（ゲーム上一つしか存在してはいけないクラス）
 */

struct FAuraGameplayTags
{
public:

  static const FAuraGameplayTags& Get(){ return GameplayTags; };

  //タグ初期化
  static void InitializeNativeGameplayTags();

  FGameplayTag Attributes_Primary_Strength;
  FGameplayTag Attributes_Primary_Intelligence;
  FGameplayTag Attributes_Primary_Resilience;
  FGameplayTag Attributes_Primary_Vigor;

  FGameplayTag Attributes_Secondary_Armor;
  FGameplayTag Attributes_Secondary_ArmorPenetration;
  FGameplayTag Attributes_Secondary_BlockChance;
  FGameplayTag Attributes_Secondary_CriticalHitChance;
  FGameplayTag Attributes_Secondary_CriticalHitDamage;
  FGameplayTag Attributes_Secondary_CriticalHitResistance;
  FGameplayTag Attributes_Secondary_HealthRegeneration;
  FGameplayTag Attributes_Secondary_ManaRegeneration;
  FGameplayTag Attributes_Secondary_MaxHealth;
  FGameplayTag Attributes_Secondary_MaxMana;

  FGameplayTag Attributes_Resistance_Fire;
  FGameplayTag Attributes_Resistance_Lightning;
  FGameplayTag Attributes_Resistance_Arcane;
  FGameplayTag Attributes_Resistance_Physical;

  FGameplayTag InputTag_LMB;
  FGameplayTag InputTag_RMB;
  FGameplayTag InputTag_1;
  FGameplayTag InputTag_2;
  FGameplayTag InputTag_3;
  FGameplayTag InputTag_4;

  FGameplayTag Damage;
  FGameplayTag Damage_Fire;
  FGameplayTag Damage_Lightning;
  FGameplayTag Damage_Arcane;
  FGameplayTag Damage_Physical;

  FGameplayTag Abilities_Attack;

  //属性と耐性をマップにしまっておく　　 
  TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
 
	 FGameplayTag Effects_HitReact;

 
protected:
 
private:
 static FAuraGameplayTags GameplayTags;
};