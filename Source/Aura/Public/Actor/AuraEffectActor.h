// Copyright Druid Mechanics
// 回復ポーションなどのアイテムのC++
// 元アクターコンポーネント

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraEffectActor();

protected:

	virtual void BeginPlay() override;

	// 効果の対象となるアクターを決定する
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GamePlayEffectClass);
	
	// ブループリント側で設置するクラス
	// 応用
	UPROPERTY(EditAnywhere, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InstanceGamePlayEffectClass;
	
};
