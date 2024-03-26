// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* Asset Tags*/);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	// デリゲート設定 DECLARE_MULTICAST_DELEGATE_OneParam(
	// デリゲート名 FEffectAssetTags,
	// デリゲートする値の型  const FGameplayTagContainer& /* Asset Tags*/);
	
	// デリゲート用関数　デリゲート名
	FEffectAssetTags EffectAssetTags;
	// デリゲート呼び出し EffectAssetTags.Broadcast(TagContainer);
	
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
protected:

	// エフェクトが起動するとデリゲートする
	void EffectApplied(
		UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& EffectSpec,
		FActiveGameplayEffectHandle ActiveEffectHandle);
	
};
