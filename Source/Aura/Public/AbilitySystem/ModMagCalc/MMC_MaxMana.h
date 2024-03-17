// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	// MMCクラスは独自のコンストラクターが必要
	// Uクラス名のコンストラクタ UMMC_MaxHealth();
public:
	UMMC_MaxMana();

	// effectspecにアクセスできる
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	// 値をキャプチャする構造体
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	
};
