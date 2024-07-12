// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);

	const float ScalableDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageType, ScalableDamage);
	
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(),UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

FDamageEffectParams UAuraDamageGameplayAbility::MakeDamageEffectParamsFromClassDefault(
	AActor* TargetActor,
	FVector InRadialDamageOrigin,
	bool bOverrideKnockbackDirection,
	FVector KnockbackDirectionOverride,
	bool bOverrideDeathImpulse,
	FVector DeathImpulseDirectionOverride,
	bool bOverridePitch,
	float PitchOverride) const
{
	FDamageEffectParams Params;
	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEEffectClass = DamageEffectClass;
	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	Params.AbilityLevel = GetAbilityLevel();
	Params.DamageType = DamageType;
	Params.DebuffChance = DebuffChance;
	Params.DebuffDamage = DebuffDamage;
	Params.DebuffDuration = DebuffDuration;
	Params.DebuffFrequency = DebuffFrequency;
	Params.DeathImpulseMagnitude = DeathImpulseMagnitude;
	Params.KnockbackChance = KnockbackChance;
	Params.KnockbackForceMagnitude = KnockbackForceMagnitude;


	if (IsValid(TargetActor))
	{
		FRotator Rotator = (TargetActor->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()).Rotation();
		if (bOverridePitch)
		{
			Rotator.Pitch = PitchOverride;
		}
		else
		{
			Rotator.Pitch = 45.f;
		}
		const FVector ToTarget = Rotator.Vector();
		if (!bOverrideKnockbackDirection) Params.KnockbackForce = ToTarget * KnockbackForceMagnitude;
		if (!bOverrideDeathImpulse) Params.DeathImpulse = ToTarget * DeathImpulseMagnitude;
	}
	
	if (bOverrideKnockbackDirection)
	{
		KnockbackDirectionOverride.Normalize();
		Params.KnockbackForce = KnockbackDirectionOverride * KnockbackForceMagnitude;
		
		// 上方向へのディレクション
		if (bOverridePitch)
		{
			FRotator KnockBackRotation = KnockbackDirectionOverride.Rotation();
			KnockBackRotation.Pitch = PitchOverride;
			Params.KnockbackForce = KnockBackRotation.Vector() * KnockbackForceMagnitude;
		}
	}

	if (bOverrideDeathImpulse)
	{	
		DeathImpulseDirectionOverride.Normalize();
		Params.DeathImpulse = DeathImpulseDirectionOverride * DeathImpulseMagnitude;
		if (bOverridePitch)
		{
			FRotator DeathImpulseRotation = DeathImpulseDirectionOverride.Rotation();
			DeathImpulseRotation.Pitch = PitchOverride;
			Params.DeathImpulse = DeathImpulseRotation.Vector() * DeathImpulseMagnitude;
		}
	}
	


	// 放射状ダメージを適応する場合
	if (bIsRadialDamage)
	{
		Params.bIsRadialDamage = bIsRadialDamage;
		Params.RadialDamageOrigin = InRadialDamageOrigin;
		Params.RadialDamageInnerRadius = RadialDamageInnerRadius;
		Params.RadialDamageOuterRadius = RadialDamageOuterRadius;
	}
	
	return Params;
}

float UAuraDamageGameplayAbility::GetDamageAtLevel() const
{
	return Damage.GetValueAtLevel(GetAbilityLevel());
}

FTagMontage UAuraDamageGameplayAbility::GetRandomTagMontageFromArray(const TArray<FTagMontage>& TagMontages) const
{
	if (TagMontages.Num() > 0)
	{
		const int32 Selection = FMath::RandRange(0, TagMontages.Num() - 1);
		return TagMontages[Selection];
	}

	return FTagMontage();
}
