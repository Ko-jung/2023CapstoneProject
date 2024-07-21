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

	{ // 변수 초기화
		RequiredTime = 1.0f;
		CurrentInteractionTime = 0.0f;
		LastInteractionTime = 0.0f;
		CurrentInteractionActor = nullptr;
		ItemEffectType = EItemEffect::EIE_Team_Speed;

		RemoveTime = 0.5f;
	}

	float SphereRadius = 100.0f;

	{
		for (int i = 0; i < (int8)EItemEffect::EIE_COUNT; ++i)
		{
			ItemObjectStaticMeshes.AddDefaulted();
		}
		static ConstructorHelpers::FObjectFinder<UStaticMesh> GodModeRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/1_1.1_1'"));
		if(GodModeRef.Succeeded())
		{
			ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Single_GodMode] = GodModeRef.Object;
		}
		
		static ConstructorHelpers::FObjectFinder<UStaticMesh> BoostBulletRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/1_2.1_2'"));
		if(BoostBulletRef.Succeeded())
		{
			ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Single_BoostBulletInfinity] = BoostBulletRef.Object;
		}
		
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Team_SpeedRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/2_1.2_1'"));
		if(Team_SpeedRef.Succeeded())
		{
			ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Team_Speed] = Team_SpeedRef.Object;
		}

		static ConstructorHelpers::FObjectFinder<UStaticMesh> Team_PowerRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/2_2.2_2'"));
		if(Team_PowerRef.Succeeded())
		{
			ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Team_Power] = Team_PowerRef.Object;
		}
		
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Team_PlusHealthRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/2_3.2_3'"));
		if(Team_PlusHealthRef.Succeeded())
		{
			ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Team_PlusHealth] = Team_PlusHealthRef.Object;
		}

		static ConstructorHelpers::FObjectFinder<UStaticMesh> Gravity_UpRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/3_1_1.3_1_1'"));
		if (Gravity_UpRef.Succeeded())
		{
			ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Gravity_Up] = Gravity_UpRef.Object;
		}

		static ConstructorHelpers::FObjectFinder<UStaticMesh> Gravity_DownRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/3_1_2.3_1_2'"));
		if (Gravity_DownRef.Succeeded())
		{
			ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Gravity_Down] = Gravity_DownRef.Object;
		}

		static ConstructorHelpers::FObjectFinder<UStaticMesh> TileCollapseRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/3_2.3_2'"));
		if (TileCollapseRef.Succeeded())
		{
			ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Tile_Break] = TileCollapseRef.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/2016180023/item/ITEM_SPAWNER.ITEM_SPAWNER'"));
		BodyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
		SetRootComponent(BodyStaticMesh);
		BodyStaticMesh->SetStaticMesh(BodyMeshRef.Object);
		BodyStaticMesh->SetRelativeScale3D(FVector{ 2.0f });

		ItemObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemObject"));
		ItemObjectMesh->SetupAttachment(BodyStaticMesh);
		ItemObjectMesh->SetStaticMesh(ItemObjectStaticMeshes[(int8)EItemEffect::EIE_Single_GodMode]);
		ItemObjectMesh->AddRelativeLocation(FVector(0.0f, 0.0f, SphereRadius / 2));
	}

	{ // CreateDefaultSubobject 
		SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
		SphereComponent->SetupAttachment(BodyStaticMesh);
		SphereComponent->SetHiddenInGame(false);
		SphereComponent->SetSphereRadius(SphereRadius);
		SphereComponent->AddRelativeLocation(FVector(0.0f, 0.0f, SphereRadius));
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
			GaugeWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
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


void ALootingItemActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	InteractionBar = Cast<UProgressBar>(GaugeWidgetComponent->GetUserWidgetObject()->GetWidgetFromName("PB_Interaction"));

	if(ItemObjectMesh)
	{
		ItemObjectMesh->SetStaticMesh(ItemObjectStaticMeshes[(uint8)ItemEffectType]);
	}
	
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
	// 사용한 캐릭터에게 아이템을 추가
	ItemUsedCharacter->AddItem(ItemEffectType, ItemRareLevel, this);



	// Destory On Server
	//Destroy();
}


void ALootingItemActor::SphereBeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TObjectPtr<ASkyscraperCharacter> OverlapCharacter = Cast<ASkyscraperCharacter>(OtherActor))
	{
		// 위젯 생성 및 연결
		if(OverlapCharacter->GetPlayerController())
		{
			UUserWidget* InteractionKeyWidget = CreateWidget(OverlapCharacter->GetPlayerController(), WBP_InteractionKey);

			if (!InteractionKeyWidget) return;

			InteractionKeyWidget->AddToViewport();
			// TMap에 [캐릭터, 위젯] 튜플 추가
			PlayerAndWidgetMap.Add(OverlapCharacter, InteractionKeyWidget);
		}
	}
}

void ALootingItemActor::SphereEndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if (PlayerAndWidgetMap.IsEmpty()) return;

	RemovePlayerWidget(OtherActor);
}

void ALootingItemActor::RemovePlayerWidget(AActor* EndOverlapCharacter)
{
	// 나간 액터가 캐릭터가 아니라면 종료
	if (!EndOverlapCharacter->IsA(ASkyscraperCharacter::StaticClass())) return;

	// 나간 액터가 현재 맵에 저장되어 있지 않을경우도 종료
	
	if (!PlayerAndWidgetMap.FindChecked(EndOverlapCharacter)) return;

	if (UUserWidget** Widget = PlayerAndWidgetMap.Find(EndOverlapCharacter))
	{
		// 뷰포트에서 제거
		(*Widget)->RemoveFromParent();

		// TMap에서 제거
		PlayerAndWidgetMap.Remove(EndOverlapCharacter);
	}
}



void ALootingItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (ItemObjectMesh)
	//{
	//	ItemObjectMesh->AddRelativeRotation(FRotator(0.0f, DeltaTime * 10, 0.0f));
	//	ItemObjectMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 100 * FMath::Sin(GetWorld()->GetTimeSeconds()) + 100.0f));
	//}

	// 0.5초 이상 상호작용 계속 진행하지 않았을 시,
	if (GetWorld()->GetTimeSeconds() - LastInteractionTime > RemoveTime)
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
	// 현재 오버랩 중인 액터에 대해서만 실행될 수 있도록
	if (!PlayerAndWidgetMap.Find(InteractionActor)) return;

	TObjectPtr<ASkyscraperCharacter> InteractionCharacter = Cast<ASkyscraperCharacter>(InteractionActor);
	if (!InteractionCharacter) return;

	// 현재 상호작용중이던 캐릭터가 없을 경우
	if (!CurrentInteractionActor)
	{
		CurrentInteractionActor = InteractionCharacter;
		SetActorTickEnabled(true);
		LastInteractionTime = GetWorld()->GetTimeSeconds();
		GaugeWidgetComponent->SetHiddenInGame(false);
	}

	// 기존 상호작용 중이던 캐릭터가 현재 상호작용 요청한 캐릭터와 같을 경우
	if (CurrentInteractionActor == InteractionCharacter)
	{
		CurrentInteractionTime += GetWorld()->GetDeltaSeconds();
		LastInteractionTime = GetWorld()->GetTimeSeconds();

		SetProgressBarPercent();

		// 시간이 채워졌다면 효과 적용하기
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