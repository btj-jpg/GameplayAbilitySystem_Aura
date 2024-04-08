// Copyright Druid Mechanics
// 複数の属性を変更できる計算クラス

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_Damage();

	// 計算に使うデータ取得
	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
