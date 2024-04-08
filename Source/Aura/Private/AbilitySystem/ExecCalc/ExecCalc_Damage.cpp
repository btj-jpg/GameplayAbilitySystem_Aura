// Copyright Druid Mechanics


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "CookerSettings.h"
#include "AbilitySystem/AuraAttributeSet.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
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
}

// 計算に使うデータ取得
void UExecCalc_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();
	
	// Get Damage Set By Coller Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

	// ターゲットがダメージブロックしたか
	float BlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().BlockChanceDef, EvaluateParameters, BlockChance);
	BlockChance = FMath::Max<float>(0.f, BlockChance);

	if (FMath::RandRange(1.f, 100.f) < BlockChance)
	{
		Damage = Damage/2;
	}

	// ターゲットのアーマー
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().ArmorDef, EvaluateParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);

	// アーマー貫通
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().ArmorPenetrationDef, EvaluateParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration);
	UE_LOG(LogTemp, Warning, TEXT("%f"), TargetArmor);

	const float EffectiveArmor = TargetArmor *= (100.f - SourceArmorPenetration)/100.f;
	Damage =  FMath::CeilToInt(Damage * (100.f - EffectiveArmor * 0.333) / 100.f);
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
