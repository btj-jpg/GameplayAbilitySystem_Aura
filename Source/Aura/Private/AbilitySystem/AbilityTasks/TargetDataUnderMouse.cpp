// Copyright Druid Mechanics


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDefaultUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	// Super::Activate(); ログを表示するだけSuper不要

	const bool bTsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	// もしクライアント側なら
	if (bTsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		// ターゲットデータを読み取る
	}
	
	
	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	// 予測キーを作成
	// AbilitySystemComponent->ScopedPredictionKey ここのスコープ範囲の指定
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get);
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	// GetActivationPredictionKey() アビリティの予測キー
	// AbilitySystemComponent->ScopedPredictionKey　アビリティ実行中のキャラクターの予測キー
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
		);

	// アビリティがアクティブなら
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
