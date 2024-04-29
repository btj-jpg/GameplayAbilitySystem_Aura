// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocation()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	//回転軸（Axis）：回転を適用する軸を指定します。これは3次元空間内のベクトルで表されます。
	//回転角度（Angle）：回転を行う角度を指定します。これはラジアン単位で表されます。
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread/2.f, FVector::UpVector);
	TArray<FVector> SpawmLocations;
	for (int32 i = 0; i < NumMinions; i ++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawmLocations.Add(ChosenSpawnLocation);
		
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 18.f, 12, FColor::Green, false, 3.f);
		UKismetSystemLibrary::DrawDebugArrow(
		GetAvatarActorFromActorInfo(),
		Location,
		Location + Direction * MaxSpawnDistance,
		4.f,
		FLinearColor::Gray,
		3.f);

		DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);
		DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);
	}
	
	return SpawmLocations;
	
}
