// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "Ui/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	virtual void PossessedBy(AController* NewController) override;

	/* Enemy Interface */
	
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;

	// 攻撃アニメーションの時などにコンバットターゲットを指定するために使う
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	
	/* End Enemy Interface */

	/* Combat Interface */
	
	virtual int32 GetPlayerLevel() override;
	virtual  void Die() override;
	
	/* End Combat Interface */

	virtual void InitializeDefaultAttributes() const override;
	
	//#include "Ui/WidgetController/OverlayWidgetController.h"
	// includeでオーバーレイウィジェットコントローラーを含めてデリゲート設定を流用する
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChanged;

	// 指定されたタグの数が変わるたびにタグをカウントする
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UFUNCTION(BlueprintCallable)
	ECharacterClass GetCharacterClass();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;

};
