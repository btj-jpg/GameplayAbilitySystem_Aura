// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const int32 ScalableDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	const float Cooldown = GetCooldown(Level);
	const float ManaCost = GetManaCost(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(

			// Title
			"<Title>ELECTROCUTE</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			// Description
			"<Default>Emits abeam of Lightning,"
			"connecting with the target, repeatedly causing</>"
			"<Damage>%d</>"
			"<Default> Lightning damage with a chance to stun</>"),

			// Values
			Level,
			ManaCost * -1,
			Cooldown,
			ScalableDamage);
	}
	else
	{
		return FString::Printf(TEXT(

			// Title
			"<Title>ELECTROCUTE</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			// number of fire bolt
			"<Default>Emits a beam of Lightning"
			"propagating to %d additional targets nearby, causing</>"
			"<Damage>%d</>"
			"<Default> lightning damage with a chance to stun</>"),

			// Values
			Level,
			ManaCost * -1,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScalableDamage);
	} 
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
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
		// number of fire bolt
		"<Default>Emits a beam of Lightning"
		"propagating to %d additional targets nearby, causing</>"
		"<Damage>%d</>"
		"<Default> lightning damage with a chance to stun</>"),

		// Values
		Level,
		ManaCost * -1,
		Cooldown,
		FMath::Min(Level, MaxNumShockTargets - 1),
		ScalableDamage);
	
}
