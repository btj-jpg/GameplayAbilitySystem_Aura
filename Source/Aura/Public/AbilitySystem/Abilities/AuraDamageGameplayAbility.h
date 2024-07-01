// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraAbilityTypes.h"
#include "AuraDamageGameplayAbility.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	UFUNCTION(Blueprintpure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefault(AActor * TargetActor = nullptr) const;

	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel() const;
	
protected:

	// ダメージを与えるエフェクト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	// ダメージの種類 種類のタグとダメージの値カーブ

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DebuffChance = 20.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DebuffDuration = 5.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DeathImpulseMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float KnockbackForceMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float KnockbackChance = 100.f;
	
	UFUNCTION(BlueprintPure)
	FTagMontage GetRandomTagMontageFromArray(const TArray<FTagMontage>& TagMontages) const;
	
};
