// Copyright Druid Mechanics


#include "Actor/PointCollection.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

APointCollection::APointCollection()
{
	PrimaryActorTick.bCanEverTick = false;

	PT_0 = CreateDefaultSubobject<USceneComponent>("PT_0");
	ImmutablePts.Add(PT_0);
	SetRootComponent(PT_0);

	PT_1 = CreateDefaultSubobject<USceneComponent>("PT_1");
	ImmutablePts.Add(PT_1);
	PT_1->SetupAttachment(GetRootComponent());

	PT_2 = CreateDefaultSubobject<USceneComponent>("PT_2");
	ImmutablePts.Add(PT_2);
	PT_2->SetupAttachment(GetRootComponent());

	PT_3 = CreateDefaultSubobject<USceneComponent>("PT_3");
	ImmutablePts.Add(PT_3);
	PT_3->SetupAttachment(GetRootComponent());

	PT_4 = CreateDefaultSubobject<USceneComponent>("PT_4");
	ImmutablePts.Add(PT_4);
	PT_4->SetupAttachment(GetRootComponent());

	PT_5 = CreateDefaultSubobject<USceneComponent>("PT_5");
	ImmutablePts.Add(PT_5);
	PT_5->SetupAttachment(GetRootComponent());

	PT_6 = CreateDefaultSubobject<USceneComponent>("PT_6");
	ImmutablePts.Add(PT_6);
	PT_6->SetupAttachment(GetRootComponent());
	
	PT_7 = CreateDefaultSubobject<USceneComponent>("PT_7");
	ImmutablePts.Add(PT_7);
	PT_7->SetupAttachment(GetRootComponent());

	PT_8 = CreateDefaultSubobject<USceneComponent>("PT_8");
	ImmutablePts.Add(PT_8);
	PT_8->SetupAttachment(GetRootComponent());

	PT_9 = CreateDefaultSubobject<USceneComponent>("PT_9");
	ImmutablePts.Add(PT_9);
	PT_9->SetupAttachment(GetRootComponent());
	
	PT_10 = CreateDefaultSubobject<USceneComponent>("PT_10");
	ImmutablePts.Add(PT_10);
	PT_10->SetupAttachment(GetRootComponent());

}

TArray<USceneComponent*> APointCollection::GetGroundPoint(const FVector& GrandLocation, int32 NumPoints,
	float YawOverride)
{
	checkf(ImmutablePts.Num() >= NumPoints, TEXT("取得するポイントが多すぎます(最大10)"));

	TArray<USceneComponent*> ArrayCopy;
	for (USceneComponent* Pt : ImmutablePts)
	{
		if (ArrayCopy.Num() >= NumPoints) return ArrayCopy;

		if (Pt != PT_0)
		{
			FVector ToPoint = Pt->GetComponentLocation() - PT_0->GetComponentLocation();
			ToPoint = ToPoint.RotateAngleAxis(YawOverride, FVector::UpVector);
			Pt->SetWorldLocation(PT_0->GetComponentLocation() + ToPoint);
		}

		const FVector RaisedLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, Pt->GetComponentLocation().Z + 500.f);
		const FVector LoweredLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, Pt->GetComponentLocation().Z - 500.f);

		FHitResult HitResult;
		TArray<AActor*> IgnoreActors;
		UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(
			this,
			IgnoreActors,
			TArray<AActor*>(),
			1500.f,
			GetActorLocation());

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(IgnoreActors);
		GetWorld()->LineTraceSingleByProfile(HitResult, RaisedLocation, LoweredLocation, FName("BlockAll"), QueryParams);

		const FVector AdjustedLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, HitResult.ImpactPoint.Z);
		Pt->SetWorldLocation(AdjustedLocation);
		Pt->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(HitResult.ImpactNormal));

		ArrayCopy.Add(Pt);
	}
	return ArrayCopy;
}

void APointCollection::BeginPlay()
{
	Super::BeginPlay();
	
}
