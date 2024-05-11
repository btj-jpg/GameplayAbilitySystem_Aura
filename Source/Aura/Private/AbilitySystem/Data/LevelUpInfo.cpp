// Copyright Druid Mechanics


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXp(int32 XPValue) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// レベル上限に達した場合
		if (LevelUpInformation.Num() - 1 < Level) return Level;

		if (XPValue >= LevelUpInformation[Level].LevelUpRequirement)
		{
			Level ++;
		}
		else
		{
			bSearching = false;	
		}
		
	}
	return Level;
}
