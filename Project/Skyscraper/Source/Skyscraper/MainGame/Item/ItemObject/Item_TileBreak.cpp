// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_TileBreak.h"

#include "Blueprint/UserWidget.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Widget/TileBreakItem/TileBreakItemWidget.h"

UItem_TileBreak::UItem_TileBreak()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_TileBreakItemRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/MainGame/Widget/TileBreakItem/WBP_TileBreakItem.WBP_TileBreakItem_C'"));
	if(WBP_TileBreakItemRef.Succeeded())
	{
		WBP_TileBreakItemClass = WBP_TileBreakItemRef.Class;
	}
}

UItem_TileBreak::~UItem_TileBreak()
{
}


void UItem_TileBreak::DoItemEffect(ASkyscraperCharacter* UsedCharacter)
{
	if (!(UsedCharacter && UsedCharacter->GetPlayerController())) return;

	UItemObject::DoItemEffect(UsedCharacter);

	UE_LOG(LogTemp, Warning, TEXT("UItem_TileBreak - DoItemEffect"));

	// 위젯 생성
	{
		if(ASkyscraperPlayerController* PlayerController = UsedCharacter->GetPlayerController())
		{
			if(WBP_TileBreakItemClass)
			{
				// 위젯 내에서 버튼 클릭시 자동으로 삭제되게 만들어 변수 저장 필요 X
				UTileBreakItemWidget* Widget = Cast<UTileBreakItemWidget>(CreateWidget(PlayerController, WBP_TileBreakItemClass));

				if(Widget)
				{
					Widget->AddToViewport();

					// 서버 TODO: UsedCharacter를 이용해 적군 캐릭터에 대한 정보 입력
					// TODO: 주의! 현재는 디버깅을 위해 아이템을 사용한 캐릭터를 0번 플레이어로 입력함
					{
						Widget->SetEnemyPlayer(0, UsedCharacter);
					}
				}
			}
			
		}
	}
	

}
