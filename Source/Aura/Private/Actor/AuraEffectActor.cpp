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

// オーバーレイ時に効果起動
void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	
	if (InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstanceGamePlayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGamePlayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGamePlayEffectClass);
	}
	
}

// オーバーレイ時に終了時起動
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{

	if (InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstanceGamePlayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGamePlayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGamePlayEffectClass);
	}

	// オーバーレイ時に終了時効果無効
	if (InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		//ActiveEffectHandles の中をloopする
		// ue5ではloop中にループの対象を削除できない
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair: ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			// マップから指定のkeyを探してそのマップをdeleteする
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
		
	}
}

// 実際にエフェクトを適応する処理
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	// アクターにアビリティシステムがあるか確かめる
	// なかったら nullptrを返す
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	check(GamePlayEffectClass);
	
	// ゲームプレイエフェクトを作成するための様々な情報のデータ構造体
	// 炎属性、ソースオブジェクトなどあらゆる情報を持つ
	/*
	 * 実行されるゲームプレイエフェクトのタイプや識別子。
	ゲームプレイエフェクトの発生元や発生先となるアクター。
	ゲームプレイエフェクトが適用されるターゲット。
	その他の実行時の条件やコンテキスト情報。など
	*/
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();

	// 内部のメンバ関数SourceObjectに対象に対するweakptrを作成する
	// weakptr 中身が見れるだけ
	EffectContextHandle.AddSourceObject(this);

	// ゲームプレイエフェクトのラッパー構造体
	// 引数1 GamePlayEffectClass Blueprintで作成できる計算などの使用
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GamePlayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// ターゲットのACSがわかれば以下のもできる
	// TargetACS->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetACS);

	// ゲームプレイエフェクトが無限か確認する
	const bool bInInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bInInfinite && InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		// ActiveGameplayEffectHandle, UAbilitySystemComponent*
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
	
}




