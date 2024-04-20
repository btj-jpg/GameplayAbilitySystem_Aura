// Copyright Druid Mechanics
// ブループリント内で使える関数を設定する

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "AuraAbilitySystemLibrary.generated.h"


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

	// オーバーレイウィジェットコントローラーをゲットする
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|WidgetController")
	static  UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	// アトリビュートウィジェットコントローラーをゲットする
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|WidgetController")
	static  UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

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

	/* AuragameplayEffectContext */
	
	// エフェクトコンテキストからブロックしたかをゲットする
	// FGameplayEffectContextHandle& = FGameplayEffectContextHandle 自体
	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	// UPARAM(ref) ブループリントで出るピンから入るピンに変更する
	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category="AuraAbillitySystemLibrary|CharacterClassDefaults")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	/* AuragameplayEffectContext End */
};
