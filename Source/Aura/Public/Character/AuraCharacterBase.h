// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UDebuffNiagaraComponent;
class UNiagaraSystem;
class UGameplayAbility;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UAnimMontage;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	/*
	 *IAbilitySystemInterfaceから継承
	 *このアクターに使用する能力システム コンポーネントを返します。
	 *const 0　はピュアバーチャル関数であることを示す
	 *virtual UAbilitySystemComponent* GetAbilitySystemComponent() const = 0;
	*/

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	// NetMulticast RPCであることを示す
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(const FVector& DeathImpulse);

	// combatInterface 
	// interfaceから継承するときは　_Implementation　がつく
	
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual TArray<FTagMontage> GetAttackMontage_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTagMontage GetTagGetMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	virtual FOnASCRegistered GetOnASCRegisteredDelegate() override;
	virtual FOnDeath GetOnDeathDelegate() override;
	
	FOnASCRegistered OnAscRegistered;
	FOnDeath OnDeath;
	
	// 攻撃モンタージュのアレイ
	UPROPERTY(EditAnywhere, Category="combat")
	TArray<FTagMontage> AttackMontages;
	
	// combatInterface end
	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	// ソケットの名前
	UPROPERTY(EditAnywhere, Category= "Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category= "Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category= "Combat")
	FName RightHandSocketName;

	UPROPERTY(EditAnywhere, Category= "Combat")
	FName TailSocketName;

	
	// アビリティシステムコンポーネントのポインター
	// レッスン22では敵の設定だけ狩猟していてプレイヤー側はnullptr
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	/*
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultResistanceAttributes;
	*/
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();

	// 自身の死亡判定
	bool bDead = false;
	
	/* ディゾルブエフェクト　*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	UNiagaraSystem* BloodEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	USoundBase* DeathSound;

	/* Minions */
	int32 MinionCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent> BurnDebuffComponent;
	
private:

	// 初期で使えるアビリティ
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	// 初期で使えるアビリティ
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;
	
	// ヒットアニメーション
	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

};


