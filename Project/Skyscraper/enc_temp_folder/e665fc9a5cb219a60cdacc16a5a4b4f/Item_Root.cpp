// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Root.h"

#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AItem_Root::AItem_Root()
{
	PrimaryActorTick.bCanEverTick = false;

	{ // 변수 초기화
		RequiredTime = 1.0f;
		CurrentInteractionTime = 0.0f;
		LastInteractionTime = 0.0f;
		CurrentInteractionActor = nullptr;
	}
	
	{ // CreateDefaultSubobject 
		SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
		SetRootComponent(SphereComponent);
		SphereComponent->SetSphereRadius(100.0f);

		GaugeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("GaugeWidget"));
		{ // 위젯 컴퍼넌트 위젯 연결 및 초기화
			static ConstructorHelpers::FClassFinder<UUserWidget> GaugeWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/ItemInteraction/WBP_InteractionGauge.WBP_InteractionGauge_C'"));
			GaugeWidgetComponent->SetWidgetClass(GaugeWidgetRef.Class);
			GaugeWidgetComponent->SetDrawSize(FVector2D(100.0f, 15.0f));
			GaugeWidgetComponent->SetHiddenInGame(true);
			GaugeWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		}
		GaugeWidgetComponent->SetupAttachment(RootComponent);

		TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ItemText"));
		{ // Text Render 초기화
			TextRenderComponent->SetText(FText::FromString(TEXT("Item")));
			TextRenderComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
			TextRenderComponent->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		}
		TextRenderComponent->SetupAttachment(RootComponent);
		
	}

	

	{ // 상호작용 키 위젯 로드
		static ConstructorHelpers::FClassFinder<UUserWidget> WBP_InteractionKeyRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/ItemInteraction/WBP_PressItemKey.WBP_PressItemKey'"));
		WBP_InteractionKey = WBP_InteractionKeyRef.Class;
	}

	
}

// Called when the game starts or when spawned
void AItem_Root::BeginPlay()
{
	Super::BeginPlay();

	
}

void AItem_Root::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for(TTuple<AActor*,UUserWidget*> PlayerAndWidget : PlayerAndWidgetMap)
	{
		PlayerAndWidget.Value->RemoveFromParent();
	}
}

// Called every frame
void AItem_Root::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem_Root::ItemInteraction(const AActor* InteractionActor)
{
}

