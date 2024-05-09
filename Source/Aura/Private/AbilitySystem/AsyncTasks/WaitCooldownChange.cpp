// Copyright Druid Mechanics


#include "AbilitySystem/AsyncTasks/WaitCooldownChange.h"
#include "AbilitySystemComponent.h"

UWaitCooldownChange* UWaitCooldownChange::WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayTag& InCooldownTag)
{
	UWaitCooldownChange* WaitCooldownChange = NewObject<UWaitCooldownChange>();
	WaitCooldownChange->ASC = AbilitySystemComponent;
	WaitCooldownChange->cooldownTag = InCooldownTag;

	if (!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid())
	{
		WaitCooldownChange->EndTask();
		return nullptr;
	}

	// タグが増減すると起動
	AbilitySystemComponent->RegisterGameplayTagEvent(InCooldownTag, EGameplayTagEventType::NewOrRemoved)
	.AddUObject(WaitCooldownChange, &UWaitCooldownChange::CoolDownTagChanged);

	// クールダウン効果がいつ適応されたかを知るために使う
	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChange, &UWaitCooldownChange::OnActiveEffectAdded);

	return WaitCooldownChange;
}

void UWaitCooldownChange::EndTask()
{
	if (!IsValid(ASC)) return;
	// デリゲートにバインドされている関数をすべてリムーブする
	ASC->RegisterGameplayTagEvent(cooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);

	// 破棄可能なことをマークする
	SetReadyToDestroy();
	MarkAsGarbage();
}


void UWaitCooldownChange::CoolDownTagChanged(const FGameplayTag InCoolDownTag, int32 NewCount)
{
	if (NewCount == 0)
	{
		CooldownEnd.Broadcast(0.f);
	}
}

void UWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetASC,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer AssetTag;
	SpecApplied.GetAllAssetTags(AssetTag);

	FGameplayTagContainer GrantedTag;
	SpecApplied.GetAllGrantedTags(GrantedTag);

	if (AssetTag.HasTagExact(cooldownTag) || GrantedTag.HasTagExact(cooldownTag))
	{
		FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(cooldownTag.GetSingleTagContainer());
		TArray<float> TimesRemainings = ASC->GetActiveEffectsTimeRemaining(GameplayEffectQuery);
		if (TimesRemainings.Num() > 0)
		{
			float TimeRemaining = TimesRemainings[0];
			for (int32 i = 0; i < TimesRemainings.Num(); i ++)
			{
				if (TimesRemainings[i] > TimeRemaining)
				{
					TimeRemaining = TimesRemainings[i];
				}
			}

			CooldownStart.Broadcast(TimeRemaining);
		}
		
	}
}
