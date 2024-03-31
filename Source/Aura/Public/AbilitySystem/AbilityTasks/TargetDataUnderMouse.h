// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);
/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
public:

	// BlueprintInternalUseOnly この関数は内部実装の詳細です。他の関数やノードを実装するために使われます。
	// HidePin入ってくるピン非表示
	UFUNCTION(
		BlueprintCallable,
		Category="Ability|Tasks",
		meta = (
			DisplayName = "TargetDataUnderMouse",
			HidePin = "OwningAbility",
			DefaultToSelf = "OwningAbility",
			BlueprintInternalUseOnly = "true"
			)
		)
	static UTargetDataUnderMouse* CreateTargetDefaultUnderMouse(UGameplayAbility* OwningAbility);

	// ブループリントでマルチデリゲートを設定する場合に使用
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

private:

	virtual void Activate() override;
	
	void SendMouseCursorData();
	
};
