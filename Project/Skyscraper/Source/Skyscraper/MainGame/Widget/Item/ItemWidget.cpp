// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

//#include "K2Node_SwitchEnum.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemWidget::SetItemImageTexture(EItemEffect ItemEffect)
{
	if(ItemImage)
	{
		ItemImage->SetBrushFromTexture(ItemTexture[(int8)ItemEffect]);
	}
	if(ItemText)
	{
		ItemText->SetText(FText::FromString(GetItemTextByEItemEffect(ItemEffect)));
		//ItemText->SetText(FText::FromString());
	}
}

void UItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

FString UItemWidget::GetItemTextByEItemEffect(EItemEffect ItemEffect)
{
	FString ReturnString;
	switch (ItemEffect)
	{
	case EItemEffect::EIE_NONE:
		ReturnString = L"";
		break;
	case EItemEffect::EIE_Single_BoostBulletInfinity:
		ReturnString = L"게이지/탄창 무한";
		break;
	case EItemEffect::EIE_Single_GodMode:
		ReturnString = L"무적(개인)";
		break;
	case EItemEffect::EIE_Team_PlusHealth:
		ReturnString = L"체력 증가(팀)";
		break;
	case EItemEffect::EIE_Team_Power:
		ReturnString = L"공격력 증가(팀)";
		break;
	case EItemEffect::EIE_Team_Speed:
		ReturnString = L"이동속도 증가(팀)";
		break;
	case EItemEffect::EIE_Gravity_Up:
		ReturnString = L"중력 증가";
		break;
	case EItemEffect::EIE_Gravity_Down:
		ReturnString = L"중력 감소";
		break;
	case EItemEffect::EIE_Tile_Break:
		ReturnString = L"타일 붕괴";
		break;
	}

	return ReturnString;
}
