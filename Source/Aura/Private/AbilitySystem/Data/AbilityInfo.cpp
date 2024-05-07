// Copyright Druid Mechanics


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool blogNotFound) const
{
	for (const FAuraAbilityInfo Info : AuraAbilityInformation)
	{	if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (blogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("タグ [%s] が見つかりませんでした [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	
	return FAuraAbilityInfo();
}
