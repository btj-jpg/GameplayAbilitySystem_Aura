// Copyright Druid Mechanics


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	// Vigor属性値をゲット
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();

	// ソース設定
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	// スナップショット設定
	IntelligenceDef.bSnapshot = false;
	

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// タグを集める
	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTag;
	EvaluateParameters.TargetTags = TargetTag;

	float Int = 0.f;

	// 計算するための属性をセット この場合は Vigor 
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParameters, Int);
	Int = FMath::Max<float>(Int, 0.f);

	//Spec.GetContext().GetSourceObject() = オーラキャラクター
	int32 PlayerLevel = 1.f;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}
	
	return (50.f + 2.5f * Int) + (15.f * PlayerLevel);
}
