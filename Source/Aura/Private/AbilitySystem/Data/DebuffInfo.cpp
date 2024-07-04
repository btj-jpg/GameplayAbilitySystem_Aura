// Copyright Druid Mechanics


#include "AbilitySystem/Data/DebuffInfo.h"

#include "GameplayEffect.h"

FDebuffInfomation UDebuffInfo::FindDebuffEffectForTag(const FGameplayTag& AttributeTag)
{

	for ( FDebuffInfomation& Info : DebuffInfos)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	
	return FDebuffInfomation();
}
