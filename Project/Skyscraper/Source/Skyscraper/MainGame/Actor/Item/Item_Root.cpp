// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Root.h"

#include "Components/ProgressBar.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

// Sets default values
AItem_Root::AItem_Root()
{
	PrimaryActorTick.bCanEverTick = true;

	{ // 변수 초기화
		RequiredTime = 1.0f;
		CurrentInteractionTime = 0.0f;
		LastInteractionTime = 0.0f;
		CurrentInteractionActor = nullptr;
	}
	
	{ // CreateDefaultSubobject 
		SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
		SetRootComponent(SphereComponent);
		SphereComponent->SetHiddenInGame(false);
		SphereComponent->SetSphereRadius(100.0f);
		SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::SphereBeginOverlapFunc);
		SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::SphereEndOverlapFunc);

		GaugeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("GaugeWidget"));
		GaugeWidgetComponent->SetupAttachment(RootComponent);
		{ // 위젯 컴퍼넌트 위젯 연결 및 초기화
			static ConstructorHelpers::FClassFinder<UUserWidget> GaugeWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/ItemInteraction/WBP_InteractionGauge.WBP_InteractionGauge_C'"));
			GaugeWidgetComponent->SetWidgetClass(GaugeWidgetRef.Class);
			GaugeWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
			GaugeWidgetComponent->SetDrawSize(FVector2D(200.0f, 30.0f));
			GaugeWidgetComponent->SetHiddenInGame(true);
			GaugeWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		}

		TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ItemText"));
		TextRenderComponent->SetupAttachment(RootComponent);
		{ // Text Render 초기화
			TextRenderComponent->SetText(FText::FromString(TEXT("Item")));
			TextRenderComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
			TextRenderComponent->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		}
		
	}

	

	{ // 상호작용 키 위젯 로드
		static ConstructorHelpers::FClassFinder<UUserWidget> WBP_InteractionKeyRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/ItemInteraction/WBP_PressItemKey.WBP_PressItemKey_C'"));
		WBP_InteractionKey = WBP_InteractionKeyRef.Class;
	}

	
}


void AItem_Root::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	InteractionBar = Cast<UProgressBar>(GaugeWidgetComponent->GetUserWidgetObject()->GetWidgetFromName("PB_Interaction"));
}

void AItem_Root::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for(TTuple<AActor*,UUserWidget*> PlayerAndWidget : PlayerAndWidgetMap)
	{
		PlayerAndWidget.Value->RemoveFromParent();
	}
}

void AItem_Root::DoItemEffect(ASkyscraperCharacter* ItemUsedCharacter)
{
	Destroy();
}


void AItem_Root::SphereBeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(TObjectPtr<ASkyscraperCharacter> OverlapCharacter = Cast<ASkyscraperCharacter>(OtherActor))
	{
		// 위젯 생성 및 연결
		UUserWidget* InteractionKeyWidget = CreateWidget(OverlapCharacter->GetPlayerController(), WBP_InteractionKey);
		InteractionKeyWidget->AddToViewport();

		// TMap에 [캐릭터, 위젯] 튜플 추가
		PlayerAndWidgetMap.Add(OverlapCharacter, InteractionKeyWidget);
	}
}

void AItem_Root::SphereEndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	RemovePlayerWidget(OtherActor);
}

void AItem_Root::RemovePlayerWidget(AActor* EndOverlapCharacter)
{
	if(UUserWidget* Widget = *PlayerAndWidgetMap.Find(EndOverlapCharacter))
	{
		// 뷰포트에서 제거
		Widget->RemoveFromParent();

		// TMap에서 제거
		PlayerAndWidgetMap.Remove(EndOverlapCharacter);
	}
}



void AItem_Root::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 0.5초 이상 상호작용 계속 진행하지 않았을 시,
	if(GetWorld()->GetTimeSeconds() - LastInteractionTime > 0.5f)
	{
		CurrentInteractionTime = 0.0f;
		GaugeWidgetComponent->SetHiddenInGame(true);
		SetActorTickEnabled(false);
		CurrentInteractionActor = nullptr;
		SetProgressBarPercent();
	}
}

void AItem_Root::ItemInteraction(AActor* InteractionActor)
{
	// 현재 오버랩 중인 액터에 대해서만 실행될 수 있도록
	if (!PlayerAndWidgetMap.Find(InteractionActor)) return;

	TObjectPtr<ASkyscraperCharacter> InteractionCharacter = Cast<ASkyscraperCharacter>(InteractionActor);
	if (!InteractionCharacter) return;

	// 현재 상호작용중이던 캐릭터가 없을 경우
	if(!CurrentInteractionActor)
	{
		CurrentInteractionActor = InteractionCharacter;
		SetActorTickEnabled(true);
		LastInteractionTime = GetWorld()->GetTimeSeconds();
		GaugeWidgetComponent->SetHiddenInGame(false);
	}

	// 기존 상호작용 중이던 캐릭터가 현재 상호작용 요청한 캐릭터와 같을 경우
	if(CurrentInteractionActor == InteractionCharacter)
	{
		CurrentInteractionTime += GetWorld()->GetDeltaSeconds();
		LastInteractionTime = GetWorld()->GetTimeSeconds();

		SetProgressBarPercent();

		// 시간이 채워졌다면 효과 적용하기
		if(CurrentInteractionTime >= RequiredTime)
		{
			DoItemEffect(InteractionCharacter);
		}
	}

}

void AItem_Root::SetProgressBarPercent() const
{
	InteractionBar->SetPercent(UKismetMathLibrary::SafeDivide(CurrentInteractionTime, RequiredTime));
}