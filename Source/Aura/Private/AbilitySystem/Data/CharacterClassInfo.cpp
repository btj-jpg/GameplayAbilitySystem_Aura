// Copyright Druid Mechanics


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
		return CharacterClassDefaultInformation.FindChecked(CharacterClass);
}