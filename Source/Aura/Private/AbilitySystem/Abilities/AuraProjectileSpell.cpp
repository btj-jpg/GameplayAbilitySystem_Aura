// Copyright Druid Mechanics

#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	// サーバーで呼び出されてるか
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	
	if (!bIsServer) return;

	//GetAvatarActorFromActorInfo() BP_AuraCharacter
	//GetOwningActorFromActorInfo() BP_AuraPlayerState このアビリティを所有するBP

	// この能力を実行している物理的なアクター GetAvatarActorFromActorInfo()
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		//Quaternion 軸と方向で3次元を表す
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		//UWorld::SpawnActorDeferred指定されたクラスを生成し、クラス T ポインタを返し、ワールド トランスフォームを強制的に設定します
		//この能力を所有するアクター GetOwningActorFromActorInfo()
		AAuraProjectile* Projectile =
		GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->FinishSpawning(SpawnTransform);
	}
}
