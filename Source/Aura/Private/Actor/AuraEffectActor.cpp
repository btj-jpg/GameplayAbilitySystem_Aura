// Copyright Druid Mechanics


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	// アクターにアビリティシステムがあるか確かめる
	// なかったら nullptrを返す
	UAbilitySystemComponent* TargetACS = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetACS == nullptr) return;
	check(GamePlayEffectClass);
	
	// ゲームプレイエフェクトを作成するための様々な情報のデータ構造体
	// 炎属性、ソースオブジェクトなどあらゆる情報を持つ
	FGameplayEffectContextHandle EffectContextHandle = TargetACS->MakeEffectContext();

	// 内部のメンバ関数SourceObjectに対象に対するweakptrを作成する
	// weakptr 中身が見れるだけ
	EffectContextHandle.AddSourceObject(this);

	// ゲームプレイエフェクトのラッパー構造体
	// GamePlayEffectClass Blueprintで作成できる計算などの使用
	FGameplayEffectSpecHandle EffectSpecHandle = TargetACS->MakeOutgoingSpec(GamePlayEffectClass, 1.0f, EffectContextHandle);
	TargetACS->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// ターゲットのACSがわかれば以下のもできる
	// TargetACS->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetACS);
}




