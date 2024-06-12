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

	GameplayTags.InputTag_Passive_1 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.Passive.1"),
			FString("Passive Ability 1")
			);

	GameplayTags.InputTag_Passive_2 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.Passive.2"),
			FString("Passive Ability 2")
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
			FName("Damage.Fire"),
			FString("Fire Damage Type")
			);

	GameplayTags.Damage_Lightning =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Lightning"),
			FString("Lightning Damage Type")
			);

	GameplayTags.Damage_Arcane =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Arcane"),
			FString("Arcane Damage Type")
			);
	
	GameplayTags.Damage_Physical =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Physical"),
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

	// デバフ
	GameplayTags.Debuff_Burn =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Debuff.Burn"),
			FString("Fire Damage Debuff")
			);

	GameplayTags.Debuff_Stun =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Debuff.Stun"),
			FString("Lightning Damage Debuff")
			);

	GameplayTags.Debuff_Arcane =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Debuff.Arcane"),
			FString("Arcane Damage Debuff")
			);

	GameplayTags.Debuff_Physical =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Debuff.Physical"),
			FString("Physical Damage Debuff")
			);

	GameplayTags.Debuff_Chance =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Debuff.Chance"),
			FString("Debuff Chance")
			);

	GameplayTags.Debuff_Damage =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Debuff.Damage"),
			FString("Debuff Damage")
			);

	GameplayTags.Debuff_Duration =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Debuff.Duration"),
			FString("Debuff Duration")
			);

	GameplayTags.Debuff_Frequency =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Debuff.Frequency"),
			FString("Debuff Frequency")
			);

	// ダメージ対応とデバフのグループ
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	

	// メタ属性（複製されない属性）
	GameplayTags.Attributes_Meta_IncomingXP =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Meta.IncomingXP"),
			FString("MetaAttribute IncomingXP")
			);

	
	
	// ヒット
	GameplayTags.Effects_HitReact =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Effects.HitReact"),
			FString("HitReact")
			);

	// アビリティ
	GameplayTags.Abilities_None =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.None"),
			FString("None Ability - likr the nullptr")
			);
	
	GameplayTags.Abilities_Attack =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Attack"),
			FString("Attack Ability Tag")
			);
	
	GameplayTags.Abilities_Summon =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Summon"),
			FString("Summon Ability Tag")
			);

	GameplayTags.Abilities_Fire_FireBolt =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Fire.FireBolt"),
			FString("FireBolt Ability Tag")
			);

	GameplayTags.Abilities_Lightning_Electrocute =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Lightning.Electrocute"),
			FString("Electrocute Ability Tag")
			);

	GameplayTags.Abilities_HitReact =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.HitReact"),
				FString("HitReact Ability Tag")
				);

	GameplayTags.Abilities_Status_Eligible =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Status.Eligible"),
				FString("Eligible Status")
				);

	GameplayTags.Abilities_Status_Equipped =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Status.Equipped"),
				FString("Equipped Status")
				);

	GameplayTags.Abilities_Status_locked =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Status.locked"),
				FString("locked Status")
				);

	GameplayTags.Abilities_Status_Unlocked =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Status.Unlocked"),
				FString("Unlocked Status")
				);

	GameplayTags.Abilities_Type_Offensive =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Type.Offensive"),
				FString("AbilitiesType Offensive")
				);

	GameplayTags.Abilities_Type_Passive =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Type.Passive"),
				FString("AbilitiesType Passive")
				);

	GameplayTags.Abilities_Type_None =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("Abilities.Type.None"),
				FString("AbilitiesType None")
				);

	
	// クールダウン
	GameplayTags.CoolDown_Fire_FireBolt =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("CoolDown.Fire.FireBolt"),
			FString("FireBolt CoolDown Tag")
			);

	// コンバットソケット
	GameplayTags.CombatSocket_Weapon =
			UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName("CombatSocket.Weapon"),
				FString("Weapon CombatSocket Tag")
				);

	GameplayTags.CombatSocket_RightHand =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("CombatSocket.RightHand"),
			FString("RightHand CombatSocket Tag")
			);

	GameplayTags.CombatSocket_LeftHand =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("CombatSocket.LeftHand"),
			FString("LeftHand CombatSocket Tag")
			);

	GameplayTags.CombatSocket_Tail =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("CombatSocket.Tail"),
			FString("Tail CombatSocket Tag")
			);

	
	// モンタージュタグ
	GameplayTags.Montage_Attack_1 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Montage.Attack.1"),
			FString("Montage Tag 1")
			);

	GameplayTags.Montage_Attack_2 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Montage.Attack.2"),
			FString("Montage Tag 2")
			);

	GameplayTags.Montage_Attack_3 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Montage.Attack.3"),
			FString("Montage Tag 3")
			);

	GameplayTags.Montage_Attack_4 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Montage.Attack.4"),
			FString("Montage Tag 4")
			);
	
}

