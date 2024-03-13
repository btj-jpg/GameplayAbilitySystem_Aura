// Copyright Druid Mechanics


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributes = CastChecked<UAuraAttributeSet>(AttributeSet);

	// 初期値をブロードキャストする
	OnHealthChanged.Broadcast(AuraAttributes->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributes->GetMaxHealth());
	
	OnManaChanged.Broadcast(AuraAttributes->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributes->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributes = CastChecked<UAuraAttributeSet>(AttributeSet);

	// AuraAttributes->GetHealthAttribute() この部分でデリゲート取得
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetHealthAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxHealthAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetManaAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxManaAttribute())
	.AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	// ラムダ式
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{

				// A.1 MatchesTag("A") true A MatchesTag("A.1") false

				// 指定したいタグ名
				FGameplayTag MessageTag =  FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					// Broadcast 生ポインターを渡さないといけない
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
	
}

/*
FOnAttributeChangeData()
		: NewValue(0.0f)
		, OldValue(0.0f)
		, GEModData(nullptr)
{ }
*/