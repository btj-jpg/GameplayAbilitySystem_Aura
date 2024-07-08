// Copyright Druid Mechanics
// ブループリント内で使える関数を設定する

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraAbilitySystemLibrary.generated.h"


class UDebuffInfo;
class AAuraHUD;
struct FWidgetControllerParams;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// AuraHUDのポインターを参照渡しする
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AAuraHUD*& OutAuraHUD);

	// オーバーレイウィジェットコントローラーをゲットする
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static  UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	// アトリビュートウィジェットコントローラーをゲットする
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static  UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static  USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);

	// 敵の初期ステータス設定　敵の種類によってステータスを変更できる
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(
		const UObject* WorldContextObject,
		ECharacterClass CharacterClass,
		float Level,
		UAbilitySystemComponent* ASC
		);

	// 初期のアビリティを付与する（初期ステータスセット）
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static UDebuffInfo* GetDebuffInfo(const UObject* WorldContextObject);
	
	/* AuragameplayEffectContext */
	
	// エフェクトコンテキストからブロックしたかをゲットする
	// FGameplayEffectContextHandle& = FGameplayEffectContextHandle 自体
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle);

	// UPARAM(ref) ブループリントで出るピンから入るピンに変更する
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	// 非コンスト参照
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInSuccessfulDebuff);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDamage);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDuration);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InFrequency);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce);
	
	/* AuragameplayEffectContext End */

	// 攻撃のあたり判定内にいるプレイヤーを見つける
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActor, const TArray<AActor*>& ActorToIgnore, float Radius, const FVector& SphereOrigin);

	// ヒットリザルトから知回数券をゲットする
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|GameplayMechanics")
	static void GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin);
	
	// 敵同士のフレインドリーファイアをなくす
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor * SecondActor);

	// 回転入手
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|GameplayMechanics")
	static TArray<FRotator> EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|GameplayMechanics")
	static TArray<FVector> EvenlyRotateVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);

	// XPの値をゲットする
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static int32 GetXPReward_ForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 Level);

	//FDamageEffectParamsからダメージゲームプレイエフェクトを実装する
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(FDamageEffectParams Params);
};
