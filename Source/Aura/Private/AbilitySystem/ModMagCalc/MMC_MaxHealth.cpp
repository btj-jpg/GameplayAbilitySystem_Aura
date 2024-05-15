// Copyright Druid Mechanics


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{

	// Vigor属性値をゲット
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();

	// ソース設定
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	// スナップショット設定
	VigorDef.bSnapshot = false;
	

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// タグを集める
	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTag;
	EvaluateParameters.TargetTags = TargetTag;

	float Vigor = 0.f;

	// 計算するための属性をセット この場合は Vigor 
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	//Spec.GetContext().GetSourceObject() = オーラキャラクター
	int32 PlayerLevel = 1.f;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}
	
	return (80.f + 2.5f * Vigor) + (10.f * PlayerLevel);
}
