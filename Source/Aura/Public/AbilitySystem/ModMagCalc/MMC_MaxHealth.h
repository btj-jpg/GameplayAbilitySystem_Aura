// Copyright Druid Mechanics
// 最大HPの計算用クラス、使用時はC++のままゲームエフェクトに追加できる

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()


	// MMCクラスは独自のコンストラクターが必要
	// Uクラス名のコンストラクタ UMMC_MaxHealth();
public:
	UMMC_MaxHealth();

	// effectspecにアクセスできる
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	// 値をキャプチャする構造体
	FGameplayEffectAttributeCaptureDefinition VigorDef;
	
};
