// Copyright Druid Mechanics


#include "AuraGameplayTags.h"

#include "AssetTypeCategories.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	// UGameplayTagsManager::Get() return SingletonManeger
	// ゲーム上に一つだけ存在するタグマネージャーにタグを追加する

	// プライマリー属性
	GameplayTags.Attributes_Primary_Strength =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Strength"),
			FString("Increases physical damage")
			);

	GameplayTags.Attributes_Primary_Intelligence =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Intelligence"),
			FString("Increases magic damage")
			);

	GameplayTags.Attributes_Primary_Resilience =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Resilience"),
			FString("Increases Armor and Armor Penetration")
			);

	GameplayTags.Attributes_Primary_Vigor =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Vigor"),
			FString("Increases Health")
			);


	// セカンダリー属性
	GameplayTags.Attributes_Secondary_Armor =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Armor"),
			FString("Reduces damage taken, Improve Block Chance")
			);

	GameplayTags.Attributes_Secondary_ArmorPenetration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.ArmorPenetration"),
			FString("Ignores Percentage of enemy Armor, increases Critical Hit Chance")
			);

	GameplayTags.Attributes_Secondary_BlockChance=
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.BlockChance"),
			FString("Chance to cut incoming damage in half")
			);

	GameplayTags.Attributes_Secondary_CriticalHitChance =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalHitChance"),
			FString("Chance to double damage plus critical hit bonus")
			);

	GameplayTags.Attributes_Secondary_CriticalHitDamage =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalHitDamage"),
			FString("Bonus damage added when a critical hit is scored")
			);

	GameplayTags.Attributes_Secondary_CriticalHitResistance =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalHitResistance"),
			FString("Reduces critical hit chance of attacking enemies")
			);

	GameplayTags.Attributes_Secondary_HealthRegeneration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.HealthRegeneration"),
			FString("Amount of Health regenerated every 1 second")
			);

	GameplayTags.Attributes_Secondary_ManaRegeneration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.ManaRegeneration"),
			FString("Amount of Mana regenerated every 1 second")
			);
	
	GameplayTags.Attributes_Secondary_MaxHealth =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxHealth"),
			FString("Maximum amount of Health obtainable")
			);

	GameplayTags.Attributes_Secondary_MaxMana =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxMana"),
			FString("Maximum amount of Mana obtainable")
			);

	// インプットタグ
	GameplayTags.InputTag_LMB =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.LMB"),
			FString("Left Mouse Button")
			);

	GameplayTags.InputTag_RMB =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.RMB"),
			FString("Right Mouse Button")
			);

	GameplayTags.InputTag_1 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.1"),
			FString("1Key")
			);

	GameplayTags.InputTag_2 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.2"),
			FString("2Key")
			);

	GameplayTags.InputTag_3 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.3"),
			FString("3Key")
			);

	GameplayTags.InputTag_4 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.4"),
			FString("4Key")
			);

	// ダメージ
	GameplayTags.Damage =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage"),
			FString("Damage")
			);


	// ダメージタイプ
	GameplayTags.Damage_Fire =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage_Fire"),
			FString("Fire Damage Type")
			);

	GameplayTags.Damage_Lightning =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage_Lightning"),
			FString("Lightning Damage Type")
			);

	GameplayTags.Damage_Arcane =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage_Arcane"),
			FString("Arcane Damage Type")
			);
	
	GameplayTags.Damage_Physical =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage_Physical"),
			FString("Physical Damage Type")
			);

	
	// 属性耐性
	GameplayTags.Attributes_Resistance_Fire =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attribute_Resistance_Fire"),
			FString("Fire Damage Resistance")
			);

	GameplayTags.Attributes_Resistance_Lightning =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attribute_Resistance_Lightning"),
			FString("Lightning Damage Resistance")
			);

	GameplayTags.Attributes_Resistance_Arcane =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attribute_Resistance_Arcane"),
			FString("Arcane Damage Resistance")
			);

	GameplayTags.Attributes_Resistance_Physical =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attribute_Resistance_Physical"),
			FString("Physical Damage Resistance")
			);

	// map に属性と耐性をセット
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	
	// ヒット
	GameplayTags.Effects_HitReact =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Effects.HitReact"),
			FString("HitReact")
			);
	
}

