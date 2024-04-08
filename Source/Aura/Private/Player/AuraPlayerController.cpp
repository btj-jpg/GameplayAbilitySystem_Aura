// Copyright Druid Mechanics


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	// レプリケーションする
	// クライアント　＝　サーバーに接続している側（プレイヤーなど）
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		// 引数2 優先度
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	// マウス設定
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// マウスがビューポートにロックされなくなる
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
	AuraInputComponent->BindAbilityAction(
		InputConfig,
		this,
		&ThisClass::AbilityInputTagPressed,
		&ThisClass::AbilityInputTagReleased,
		&ThisClass::AbilityInputTagHeld
		);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

// ダメージテキストを表示する
void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageTextComonentClass)
	{
		
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComonentClass);

		// コンポーネントを動的に作成する際に必要
		DamageText->RegisterComponent();

		// キャラクターの位置に作成されその場に残る
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount);
	}
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		// FindLocationClosestToWorldLocation　指定位置に最も近いスプラインポイントを返す
		const FVector LocationOnSpline =
			Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World);

		// FindLocationClosestToWorldLocation　指定位置に最も近いスプラインポイントのベクトルを返す
		const FVector Direction =
			Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);

		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
		
	}
}


void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighLightActor();
		if (ThisActor) ThisActor->HighLightActor();
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// InputTag が　InputTag_LMB と同じか確かめる
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		// ThisActor マウスの下に敵キャラクターがいればtrue
		bTargeting = ThisActor ? true : false;

		// 話した時点での時間を参照するためfalseにしておく
		bAutoRunning = false;
	}
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	// もしボタン押している間そのボタンに割り当てられているタグが左マウスボタン以外なら
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	if (!bTargeting && !bShiftKeyDown)
	{
		// ちょっとしか押してない場合、その地点に移動
		APawn* ControlledPawn = GetPawn<APawn>();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			
			//目標地点までのパスを作成
			if (
				UNavigationPath* NavPath =
				UNavigationSystemV1::FindPathToLocationSynchronously(
					this,
					ControlledPawn->GetActorLocation(),
					CachedDestination))
			{
				Spline->ClearSplinePoints();
				// NavPath->PathPoints = TArray
				// PointLoc = FVector
				for (const FVector& PointLoc : NavPath->PathPoints) {
					//ESplineCoordinateSpace 標空間のタイプ World or Local
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}

				// 最後に生成されたパスの位置まで移動するようにする
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	// もしボタン押している間そのボタンに割り当てられているタグが左マウスボタン以外なら
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	// 入力が左クリックの場合
	if (bTargeting || bShiftKeyDown)
	{
		// マウスの下に敵がいた場合
		if (GetASC())GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		// マウスの位置に移動
		FollowTime += GetWorld()->GetDeltaSeconds();

		// マウス位置を取得
		if (CursorHit.bBlockingHit)CachedDestination = CursorHit.ImpactPoint;


		// マウス位置へのベクトル移動
		if (APawn* ControlledPawn = GetPawn<APawn>())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

// オーラアビリティシステムコンポーネントを返す
UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVecter = InputActionValue.Get<FVector2d>();
	const FRotator Rotation =  GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ConttollePawn = GetPawn<APawn>())
	{
		ConttollePawn->AddMovementInput(ForwardDirection, InputAxisVecter.Y);
		ConttollePawn->AddMovementInput(RightDirection, InputAxisVecter.X);
	}
}

