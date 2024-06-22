// Copyright Druid Mechanics


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{

	//属性（Attribute）をキャプチャするための定義
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);

	// resistance
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	//キャプチャしたものを具体化する　インスタンス化
	// FGameplayEffectAttributeCaptureDefinition を生成
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatic()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatic().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatic().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatic().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatic().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatic().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatic().CriticalHitResistanceDef);

	RelevantAttributesToCapture.Add(DamageStatic().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatic().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatic().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatic().PhysicalResistanceDef);
}

void UExecCalc_Damage::DeterminedDebuff(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FGameplayEffectSpec& Spec,
	FAggregatorEvaluateParameters EvaluateParameters,
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	
	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamege = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamege > -0.5f)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *DamageType.ToString());
			
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);
			
			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag], EvaluateParameters, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);
			const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			
			if (bDebuff)
			{
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();
				
				UAuraAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
				UAuraAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				const float DebuffDamage =  Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);

				UAuraAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UAuraAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
			}
			
		}

	}
}

// 計算に使うデータ取得
// 計算に使う初期数値を設定している
void UExecCalc_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;

	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Secondary_Armor, DamageStatic().ArmorDef);
	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Secondary_BlockChance, DamageStatic().BlockChanceDef);
	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Secondary_ArmorPenetration, DamageStatic().ArmorPenetrationDef);
	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitChance, DamageStatic().CriticalHitChanceDef);
	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitDamage, DamageStatic().CriticalHitDamageDef);
	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitResistance, DamageStatic().CriticalHitResistanceDef);

	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Resistance_Fire, DamageStatic().FireResistanceDef);
	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Resistance_Lightning, DamageStatic().LightningResistanceDef);
	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Resistance_Arcane, DamageStatic().ArcaneResistanceDef);
	TagsToCaptureDefs.Add(FAuraGameplayTags::Get().Attributes_Resistance_Physical, DamageStatic().PhysicalResistanceDef);
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1.f;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}

	int32 TargetPlayerLevel = 1.f;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// タグを追加できるパラメーター
	FAggregatorEvaluateParameters EvaluateParameters;
	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();


	// デバフ
	DeterminedDebuff(ExecutionParams, Spec, EvaluateParameters, TagsToCaptureDefs);
	
	// TTuple 複数の型を指定する時に使える
	float Damage = 0.f;
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		// ResistanceTagがなければ　ログを出してい終了する
		checkf(TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaputureDesfs doesn`t contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		
		// TagsToCaptureDefs 特定のタグがあるか検索する
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];

		// 引数2 false ダメージタイプが存在しないなら計算しない
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag, false);
	
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;
	
		Damage += DamageTypeValue;
	
	}

	// クリティカルヒット計算

	// クリティカルヒットチャンス
	float CriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().CriticalHitChanceDef, EvaluateParameters, CriticalHitChance);
	CriticalHitChance = FMath::Max<float>(0.f, CriticalHitChance);
	
	// クリティカルヒット抵抗
	float CriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().BlockChanceDef, EvaluateParameters, CriticalHitResistance);
	CriticalHitResistance = FMath::Max<float>(0.f, CriticalHitResistance);
	
	bool bCritical = false;
	float ExecutionCriticalHitChance = FMath::Max<float>(1.f, CriticalHitChance - CriticalHitResistance);
	if (FMath::RandRange(1.f, 100.f) < ExecutionCriticalHitChance)
	{
		// クリティカルヒットダメージ
		float CriticalHitDamage = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().CriticalHitDamageDef, EvaluateParameters, CriticalHitDamage);
		CriticalHitDamage = FMath::Max<float>(0.f, CriticalHitDamage);

		Damage *= 2;
		Damage += CriticalHitDamage + FMath::RandRange(1.f, 10.f);

		bCritical = true;
	}
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCritical);
	
	// ターゲットがダメージブロックしたか
	bool bBlocked = false;
	if (!bCritical)
	{
		
		float BlockChance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().BlockChanceDef, EvaluateParameters, BlockChance);
		BlockChance = FMath::Max<float>(0.f, BlockChance);

		bBlocked = FMath::RandRange(1.f, 100.f) < BlockChance;
		
		Damage = bBlocked ? Damage/2.f : Damage;
		
	}
	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

	// ターゲットのアーマー
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().ArmorDef, EvaluateParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);

	// アーマー貫通
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().ArmorPenetrationDef, EvaluateParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);
	
	const float EffectiveArmor = TargetArmor *= (100.f - SourceArmorPenetration * ArmorPenetrationCoefficient)/100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);
	
	Damage =  FMath::CeilToInt(Damage * (100.f - EffectiveArmor * EffectiveArmorCoefficient) / 100.f);
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);

	// 単純な足し算を行うように設定する
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
