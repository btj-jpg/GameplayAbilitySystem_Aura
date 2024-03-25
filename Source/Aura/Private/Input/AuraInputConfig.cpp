// Copyright Druid Mechanics


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool blogNotFound) const
{

	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (blogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("インプットアクションを見つけられませんでした タグ[%s]、クラス[%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
