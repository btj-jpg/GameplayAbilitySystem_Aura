// Copyright Druid Mechanics


#include "UI/WidgetController/OverlayWidgetController.h"

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
	.AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxHealthAttribute())
	.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetManaAttribute())
	.AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxManaAttribute())
	.AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	
}

/*
FOnAttributeChangeData()
		: NewValue(0.0f)
		, OldValue(0.0f)
		, GEModData(nullptr)
{ }
*/

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
