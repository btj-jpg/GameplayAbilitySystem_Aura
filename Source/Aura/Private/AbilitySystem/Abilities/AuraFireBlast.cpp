// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 ScalableDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	const float Cooldown = GetCooldown(Level);
	const float ManaCost = GetManaCost(Level);
	return FString::Printf(TEXT(

			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			// number of fire balls
			"<Default>Launches %d</>"
			"<Default> fire balls in all directions, each coming back and </>"
			"<Default>exploding upon return, causing</>"

			// damage
			"<Damage>%d</><Default>radial fire damage with"
			"a chance to burn</>"
			),

			// Values
			Level,
			ManaCost * -1,
			Cooldown,
			FMath::Min(Level, NumFireBalls),
			ScalableDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{
	const int32 ScalableDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	const float Cooldown = GetCooldown(Level);
	const float ManaCost = GetManaCost(Level);
	return FString::Printf(TEXT(

			// Title
			"<Title>NEXT LEVEL</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			// number of fire balls
			"<Default>Launches %d</>"
			"<Default> fire balls in all directions, each coming back and </>"
			"<Default>exploding upon return, causing</>"

			// damage
			"<Damage>%d</><Default>radial fire damage with"
			"a chance to burn</>"
			),

			// Values
			Level,
			ManaCost * -1,
			Cooldown,
			FMath::Min(Level, NumFireBalls),
			ScalableDamage);
}