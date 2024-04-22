// Copyright Druid Mechanics
// CombatInterface
// 複数の異なるclassに同様の関数を持たせたい時などに使う
// 例 敵キャラクターとプレイヤーキャラクター

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

USTRUCT(BlueprintType)
struct FTagMontage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MontageTag;
	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UAnimMontage;

/**
 * 
 */

class AURA_API ICombatInterface
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();

	/*
	 *BlueprintImplementableEvent は基本的な実装を持つ関数を Blueprint 内で拡張するためのものであり、
	 *BlueprintNativeEvent はC++での実装と同時にBlueprint内での実装を提供するもの
	*/
	
	// BlueprintNativeEvent　はもともとの所有者は定義の必要なし
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	// ブループリント側でネイティブバージョンを自動生成する
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	// =0　でピュアファンクションであることを表す
	virtual void Die() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	// アクターはゲーム内のオブジェクト全般を指し、アバターはプレイヤーが操作するキャラクターを指します
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FTagMontage> GetAttackMontage();
	
};
