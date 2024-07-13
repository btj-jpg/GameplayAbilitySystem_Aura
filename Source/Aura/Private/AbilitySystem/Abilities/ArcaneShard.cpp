// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/ArcaneShard.h"

FString UArcaneShard::GetDescription(int32 Level)
{
	const int32 ScalableDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	const float Cooldown = GetCooldown(Level);
	const float ManaCost = GetManaCost(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(

			// Title
			"<Title>ARCANE SHARD</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			// Description
			"<Default>Summon shards of arcane energy"
			"causing radial arcane damage of </>"
			"<Damage>%d</>"
			"<Default> at the shard origin.</>"),

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
			"<Title>ARCANE SHARD</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			// Description
			"<Default>Summon %d shards of arcane energy"
			"causing radial arcane damage of </>"

			"<Damage>%d</><Default> at the shard origins.</>"),

			// Values
			Level,
			ManaCost * -1,
			Cooldown,
			FMath::Min(Level, MaxNumShards),
			ScalableDamage);
	} 
}

FString UArcaneShard::GetNextLevelDescription(int32 Level)
{
	const int32 ScalableDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	const float Cooldown = GetCooldown(Level);
	const float ManaCost = GetManaCost(Level);
	
	return FString::Printf(TEXT(

			// Title
			"<Title>ARCANE SHARD</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			// Description
			"<Default>Summon %d shards of arcane energy"
			"causing radial arcane damage of </>"

			"<Damage>%d</><Default> at the shard origins.</>"),

			// Values
			Level,
			ManaCost * -1,
			Cooldown,
			FMath::Min(Level, MaxNumShards),
			ScalableDamage);
}
