// Fill out your copyright notice in the Description page of Project Settings.


#include "LootingItemActor.h"

#include "Components/ProgressBar.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"

// Sets default values
ALootingItemActor::ALootingItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	{ // ���� �ʱ�ȭ
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
		{ // ���� ���۳�Ʈ ���� ���� �� �ʱ�ȭ
			static ConstructorHelpers::FClassFinder<UUserWidget> GaugeWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/ItemInteraction/WBP_InteractionGauge.WBP_InteractionGauge_C'"));
			GaugeWidgetComponent->SetWidgetClass(GaugeWidgetRef.Class);
			GaugeWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
			GaugeWidgetComponent->SetDrawSize(FVector2D(200.0f, 30.0f));
			GaugeWidgetComponent->SetHiddenInGame(true);
			GaugeWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		}

		TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ItemText"));
		TextRenderComponent->SetupAttachment(RootComponent);
		{ // Text Render �ʱ�ȭ
			TextRenderComponent->SetText(FText::FromString(TEXT("Item")));
			TextRenderComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
			TextRenderComponent->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		}

	}



	{ // ��ȣ�ۿ� Ű ���� �ε�
		static ConstructorHelpers::FClassFinder<UUserWidget> WBP_InteractionKeyRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/ItemInteraction/WBP_PressItemKey.WBP_PressItemKey_C'"));
		WBP_InteractionKey = WBP_InteractionKeyRef.Class;
	}


}


void ALootingItemActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	InteractionBar = Cast<UProgressBar>(GaugeWidgetComponent->GetUserWidgetObject()->GetWidgetFromName("PB_Interaction"));
}

void ALootingItemActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (TTuple<AActor*, UUserWidget*> PlayerAndWidget : PlayerAndWidgetMap)
	{
		PlayerAndWidget.Value->RemoveFromParent();
	}
}

void ALootingItemActor::AddItemToUsedCharacter(ASkyscraperCharacter* ItemUsedCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("DoItemEffect"));
	// ����� ĳ���Ϳ��� �������� �߰�
	ItemUsedCharacter->AddItem(ItemEffectType, ItemRareLevel);

	Destroy();
}


void ALootingItemActor::SphereBeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TObjectPtr<ASkyscraperCharacter> OverlapCharacter = Cast<ASkyscraperCharacter>(OtherActor))
	{
		// ���� ���� �� ����
		UUserWidget* InteractionKeyWidget = CreateWidget(OverlapCharacter->GetPlayerController(), WBP_InteractionKey);
		InteractionKeyWidget->AddToViewport();

		// TMap�� [ĳ����, ����] Ʃ�� �߰�
		PlayerAndWidgetMap.Add(OverlapCharacter, InteractionKeyWidget);
	}
}

void ALootingItemActor::SphereEndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	RemovePlayerWidget(OtherActor);
}

void ALootingItemActor::RemovePlayerWidget(AActor* EndOverlapCharacter)
{
	if (UUserWidget* Widget = *PlayerAndWidgetMap.Find(EndOverlapCharacter))
	{
		// ����Ʈ���� ����
		Widget->RemoveFromParent();

		// TMap���� ����
		PlayerAndWidgetMap.Remove(EndOverlapCharacter);
	}
}



void ALootingItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 0.5�� �̻� ��ȣ�ۿ� ��� �������� �ʾ��� ��,
	if (GetWorld()->GetTimeSeconds() - LastInteractionTime > 0.5f)
	{
		CurrentInteractionTime = 0.0f;
		GaugeWidgetComponent->SetHiddenInGame(true);
		SetActorTickEnabled(false);
		CurrentInteractionActor = nullptr;
		SetProgressBarPercent();
	}
}

void ALootingItemActor::ItemInteraction(AActor* InteractionActor)
{
	// ���� ������ ���� ���Ϳ� ���ؼ��� ����� �� �ֵ���
	if (!PlayerAndWidgetMap.Find(InteractionActor)) return;

	TObjectPtr<ASkyscraperCharacter> InteractionCharacter = Cast<ASkyscraperCharacter>(InteractionActor);
	if (!InteractionCharacter) return;

	// ���� ��ȣ�ۿ����̴� ĳ���Ͱ� ���� ���
	if (!CurrentInteractionActor)
	{
		CurrentInteractionActor = InteractionCharacter;
		SetActorTickEnabled(true);
		LastInteractionTime = GetWorld()->GetTimeSeconds();
		GaugeWidgetComponent->SetHiddenInGame(false);
	}

	// ���� ��ȣ�ۿ� ���̴� ĳ���Ͱ� ���� ��ȣ�ۿ� ��û�� ĳ���Ϳ� ���� ���
	if (CurrentInteractionActor == InteractionCharacter)
	{
		CurrentInteractionTime += GetWorld()->GetDeltaSeconds();
		LastInteractionTime = GetWorld()->GetTimeSeconds();

		SetProgressBarPercent();

		// �ð��� ä�����ٸ� ȿ�� �����ϱ�
		if (CurrentInteractionTime >= RequiredTime)
		{
			AddItemToUsedCharacter(InteractionCharacter);
		}
	}

}

void ALootingItemActor::SetProgressBarPercent() const
{
	InteractionBar->SetPercent(UKismetMathLibrary::SafeDivide(CurrentInteractionTime, RequiredTime));
}