// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorActor.h"

#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/Subsystem/SkyscraperEngineSubsystem.h"

AElevatorActor::AElevatorActor()
{
	RequiredTime = 3.0f;

	ItemObjectStaticMeshes.Empty();

	BodyStaticMesh->DestroyComponent();
	BodyStaticMesh = nullptr;
	ItemObjectMesh->DestroyComponent();
	ItemObjectMesh = nullptr;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(SceneComponent);

	LeftDoor->SetRelativeLocation(FVector{ 0.0f,DoorOffset,0.0f });

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(SceneComponent);
	RightDoor->SetRelativeLocation(FVector{ 0.0f,-DoorOffset,0.0f });

	SphereComponent->SetupAttachment(SceneComponent);
	SphereComponent->SetSphereRadius(10.0f);

	GaugeWidgetComponent->SetupAttachment(SphereComponent);
	TextRenderComponent->SetupAttachment(SphereComponent);

	RemoveTime = 1.5f;

	ElevatorLocationOffset = FVector{ -1115.0f,-725.0f,-1075.0f };


	static ConstructorHelpers::FClassFinder<UUserWidget> FadeInWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/FadeIn_Out/WBP_FadeIn.WBP_FadeIn_C'"));
	if(FadeInWidgetRef.Succeeded())
	{
		FadeInWidgetClass = FadeInWidgetRef.Class;
	}
	
}

void AElevatorActor::ItemInteraction(AActor* InteractionActor)
{
	// 현재 오버랩 중인 액터에 대해서만 실행될 수 있도록
	if (!PlayerAndWidgetMap.Find(InteractionActor)) return;

	TObjectPtr<ASkyscraperCharacter> InteractionCharacter = Cast<ASkyscraperCharacter>(InteractionActor);
	if (!InteractionCharacter) return;

	//Door 를 바라보면서 상호작용 중 일때만 가능하도록
	if(!UKismetMathLibrary::InRange_FloatFloat(InteractionCharacter->GetActorRotation().Yaw - GetActorRotation().Yaw, -15.0f, 15.0f))
	{
		return;
	}
	

	// 현재 상호작용중이던 캐릭터가 없을 경우
	if (!CurrentInteractionActor)
	{
		CurrentInteractionActor = InteractionCharacter;
		SetActorTickEnabled(true);
		LastInteractionTime = GetWorld()->GetTimeSeconds();
		GaugeWidgetComponent->SetHiddenInGame(false);
		SetProgressBarPercent();
	}

	// 기존 상호작용 중이던 캐릭터가 현재 상호작용 요청한 캐릭터와 같을 경우
	if (CurrentInteractionActor == InteractionCharacter)
	{
		CurrentInteractionTime += GetWorld()->GetDeltaSeconds();
		LastInteractionTime = GetWorld()->GetTimeSeconds();

		SetProgressBarPercent();

		// 시간이 채워졌다면 효과 적용하기
		if (CurrentInteractionTime >= RequiredTime && GetWorld()->GetTimeSeconds() >= InteractionCooldownTime+1.5f )
		{
			//AddItemToUsedCharacter(InteractionCharacter);
			ApplyElevator(InteractionCharacter);
		}
	}
}

void AElevatorActor::SetProgressBarPercent() const
{
	Super::SetProgressBarPercent();
	if(LeftDoor && RightDoor)
	{
		float Value = FMath::Lerp(DoorOffset, 0.0f , UKismetMathLibrary::SafeDivide(CurrentInteractionTime, RequiredTime));
		Value = FMath::Clamp(0.0f, Value, DoorOffset);

		LeftDoor->SetRelativeLocation(FVector{ 0.0f,Value,0.0f });
		RightDoor->SetRelativeLocation(FVector{ 0.0f,-Value,0.0f });
	}
}

void AElevatorActor::ElevatorTimerAction()
{
	if(ElevatorApplyCharacter)
	{
		ElevatorApplyCharacter->SetActorRotation(GetActorRotation());
		ElevatorApplyCharacter->SetActorLocation(ElevatorDestination + ElevatorLocationOffset.RotateAngleAxis(GetActorRotation().Yaw,FVector{0.0f,0.0f,1.0f}));
		USoundBase* ElevatorStartSound = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>()->GetSkyscraperSound(TEXT("ElevatorArrive"));
		UGameplayStatics::PlaySound2D(GetWorld(), ElevatorStartSound);
		ElevatorApplyCharacter = nullptr;
	}
}

void AElevatorActor::ApplyElevator(ASkyscraperCharacter* InteractionCharacter)
{
	if(InteractionCharacter)
	{
		if(InteractionCharacter->GetPlayerController())
		{
			InteractionCooldownTime = GetWorld()->GetTimeSeconds();
			UUserWidget* UserWidget = (CreateWidget(InteractionCharacter->GetPlayerController(), FadeInWidgetClass));
			if(UserWidget)
			{
				UserWidget->AddToViewport();
			}
			ElevatorApplyCharacter = InteractionCharacter;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::ElevatorTimerAction, 1.5f, false, 1.5f);

			USoundBase* ElevatorStartSound = GEngine->GetEngineSubsystem<USkyscraperEngineSubsystem>()->GetSkyscraperSound(TEXT("ElevatorStart"));
			UGameplayStatics::PlaySound2D(GetWorld(), ElevatorStartSound);
		}
		
		
	}
}

void AElevatorActor::StartInteractionByServer()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] AElevatorActor::StartInteractionByServer"), *UKismetSystemLibrary::GetDisplayName(this));
	//IsInteractByServer = true;
	SetActorTickEnabled(true);
	if (!InteractTimer.IsValid())
	{
		LastInteractionTime = GetWorld()->GetTimeSeconds();
		InteractDelegate.BindUFunction(this, FName("Interacting"), 0.1f);
		GetWorld()->GetTimerManager().SetTimer(InteractTimer, InteractDelegate, 0.1f, true);
	}
}

void AElevatorActor::StopInteractionByServer()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] AElevatorActor::StopInteractionByServer"), *UKismetSystemLibrary::GetDisplayName(this));
	//IsInteractByServer = false;
	//SetActorTickEnabled(false);
	if (InteractTimer.IsValid())
	{
		CurrentInteractionTime = 0.f;
		GetWorld()->GetTimerManager().ClearTimer(InteractTimer);
	}
}

void AElevatorActor::Interacting(float DeltaTime)
{
	CurrentInteractionTime += DeltaTime;
	LastInteractionTime = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("[%s] AElevatorActor::Interacting LastInteractionTime: %f"), *UKismetSystemLibrary::GetDisplayName(this), LastInteractionTime);
	if (LeftDoor && RightDoor)
	{
		float Value = FMath::Lerp(DoorOffset, 0.0f, UKismetMathLibrary::SafeDivide(CurrentInteractionTime, RequiredTime));
		Value = FMath::Clamp(0.0f, Value, DoorOffset);

		LeftDoor->SetRelativeLocation(FVector{ 0.0f,Value,0.0f });
		RightDoor->SetRelativeLocation(FVector{ 0.0f,-Value,0.0f });
	}

	//if (CurrentInteractionTime > RequiredTime - 0.3f)
	//{
	//	UKismetSystemLibrary::Delay(this, 2.0f, FLatentActionInfo());
	//	CurrentInteractionTime = 0.f;
	//}
}
