// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Aura/Public/AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScalableDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	const float Cooldown = GetCooldown(Level);
	const float ManaCost = GetManaCost(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(

			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			// Description
			"<Default>Launches a bolt of fire,"
			" exploding on impact and dealing: </>"
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>"),

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
			"<Title>FIRE BOLT</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			// number of fire bolt
			"<Default>Launches %d bolts of fire,"
			" exploding on impact and dealing: </>"
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>"),

			// Values
			Level,
			ManaCost * -1,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScalableDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScalableDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	const float Cooldown = GetCooldown(Level);
	const float ManaCost = GetManaCost(Level);
	return FString::Printf(TEXT(

			// Title
			"<Title>Next Level:</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			// number of fire bolt
			"<Default>Launches %d bolts of fire,"
			" exploding on impact and dealing: </>"
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>"),

			// Values
			Level,
			ManaCost * -1,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScalableDamage);
}