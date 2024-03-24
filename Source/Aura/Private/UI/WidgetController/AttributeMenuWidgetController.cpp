// Copyright Druid Mechanics


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	/*
	初期設定
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
	*/
	
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);

		// Pair (key tag名, Value 属性(get属性attribute)
		// Execute バインドされている関数を実行する ここでは<get属性attribute>で属性が帰ってくる
		// 例　Strength
		// GetNumericValue 属性の現在の値を返します。
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}

}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{


	
}
