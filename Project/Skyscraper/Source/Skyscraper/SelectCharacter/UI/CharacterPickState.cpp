#include "CharacterPickState.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Core/SelectCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/SkyscraperGameMode.h"

// Fill out your copyright notice in the Description page of Project Settings.

UCharacterPickState::UCharacterPickState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	IsBinding(false),
	PlayerSerialNum(-1)
{
	
}

void UCharacterPickState::NativeConstruct()
{
	Super::NativeConstruct();

	// CharacterButton0->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
	// MeleeButton0->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
	// RangeButton0->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);

	{

		CharacterImgs.Add(CharacterImg);
		CharacterImgs.Add(CharacterImg_1);
		CharacterImgs.Add(CharacterImg_2);
		CharacterImgs.Add(CharacterImg_3);
		CharacterImgs.Add(CharacterImg_4);
		CharacterImgs.Add(CharacterImg_5);

		MeleeImgs.Add(MeleeImg);
		MeleeImgs.Add(MeleeImg_1);
		MeleeImgs.Add(MeleeImg_2);
		MeleeImgs.Add(MeleeImg_3);
		MeleeImgs.Add(MeleeImg_4);
		MeleeImgs.Add(MeleeImg_5);

		RangeImgs.Add(RangeImg);
		RangeImgs.Add(RangeImg_1);
		RangeImgs.Add(RangeImg_2);
		RangeImgs.Add(RangeImg_3);
		RangeImgs.Add(RangeImg_4);
		RangeImgs.Add(RangeImg_5);

		PlayerIDs.Add(PlayerId);
		PlayerIDs.Add(PlayerId_1);
		PlayerIDs.Add(PlayerId_2);
		PlayerIDs.Add(PlayerId_3);
		PlayerIDs.Add(PlayerId_4);
		PlayerIDs.Add(PlayerId_5);

		CharacterButtons.Add(CharacterButton);
		CharacterButtons.Add(CharacterButton_1);
		CharacterButtons.Add(CharacterButton_2);
		CharacterButtons.Add(CharacterButton_3);
		CharacterButtons.Add(CharacterButton_4);
		CharacterButtons.Add(CharacterButton_5);

		MeleeButtons.Add(MeleeButton);
		MeleeButtons.Add(MeleeButton_1);
		MeleeButtons.Add(MeleeButton_2);
		MeleeButtons.Add(MeleeButton_3);
		MeleeButtons.Add(MeleeButton_4);
		MeleeButtons.Add(MeleeButton_5);

		RangeButtons.Add(RangeButton);
		RangeButtons.Add(RangeButton_1);
		RangeButtons.Add(RangeButton_2);
		RangeButtons.Add(RangeButton_3);
		RangeButtons.Add(RangeButton_4);
		RangeButtons.Add(RangeButton_5);
	}

	for (const auto& Button : CharacterButtons) Button->SetIsEnabled(false);
	for (const auto& Button : MeleeButtons)		Button->SetIsEnabled(false);
	for (const auto& Button : RangeButtons)		Button->SetIsEnabled(false);

 	auto gamemode = UGameplayStatics::GetGameMode(this);
	Gamemode = static_cast<ASkyscraperGameMode*>(gamemode);

	SetOwnButtonOnClicked();
}

void UCharacterPickState::NativeDestruct()
{
	Super::NativeDestruct();
}

//void UCharacterPickState::Tick(FGeometry MyGeometry, float InDeltaTime)
//{
//	Super::Tick(MyGeometry, InDeltaTime);
//
//	if (IsInfoChanged)
//	{
//		SelectInfoUpdate();
//		IsInfoChanged = false;
//	}
//
//}

void UCharacterPickState::SelectInfoUpdate()
{
	TArray<PPlayerSelectInfo*>& PlayerSelectInfos = Gamemode->GetPlayerSelectInfo();

	// 자신이 TeamA인지 TeamB인지 판단
	bool IsRight = PlayerSerialNum >= MAXPLAYER / 2;


	for (int i = 0; i < PlayerSelectInfos.Num() / 2; i++)
	{
		int num = i + IsRight * MAXPLAYER / 2;
		auto CharacterNum = PlayerSelectInfos[num]->PickedCharacter;
		auto MeleeWeaponNum = PlayerSelectInfos[num]->PickedMeleeWeapon;
		auto RangeWeaponNum = PlayerSelectInfos[num]->PickedRangeWeapon;

		// Set Character portrait
		if (CharacterNum == ECharacterSelect::ECS_Null)
		{
			CharacterImgs[i]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			CharacterImgs[i]->SetBrushFromTexture(*CharacterImages.Find(CharacterNum));
		}

		// Set Melee Weapon portrait
		if (MeleeWeaponNum == EMeleeSelect::EMS_NONE)
		{
			MeleeImgs[i]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			MeleeImgs[i]->SetBrushFromTexture(*MeleeImages.Find(MeleeWeaponNum));
		}

		// Set Melee Weapon portrait
		if (RangeWeaponNum == ERangeSelect::ERS_NONE)
		{
			RangeImgs[i]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			RangeImgs[i]->SetBrushFromTexture(*RangeImages.Find(RangeWeaponNum));
		}
	}
}

void UCharacterPickState::SetPlayerIDs(TArray<FString> IDs, int SerialNum)
{
	// bool IsRight = SerialNum >= MAXPLAYER / 2;
	// PlayerSerialNum = SerialNum + IsRight * 6 / 2;
	PlayerSerialNum = SerialNum;

	for (int i = 0; i < MAXPLAYER; i++)
	{
		if (IDs.IsValidIndex(i) && PlayerIDs.IsValidIndex(i) && !IDs[i].IsEmpty())
		{
			PlayerIDs[i]->SetText(FText::FromString(IDs[i]));
		}
	}
	PlayerIDs[PlayerSerialNum]->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));

	SetOwnButtonOnClicked();
}

void UCharacterPickState::SetOwnButtonOnClicked()
{
	if (!CharacterButtons.IsValidIndex(PlayerSerialNum)) return;

	CharacterButtons[PlayerSerialNum]->SetIsEnabled(true);
	MeleeButtons[PlayerSerialNum]->SetIsEnabled(true);
	RangeButtons[PlayerSerialNum]->SetIsEnabled(true);

	if (!IsBinding)
	{
		CharacterButtons[PlayerSerialNum]->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
		MeleeButtons[PlayerSerialNum]->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
		RangeButtons[PlayerSerialNum]->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);

		IsBinding = true;
	}
}

UButton* UCharacterPickState::GetMyCharacterBorder() const
{
	if (CharacterButtons.IsValidIndex(PlayerSerialNum))	return CharacterButtons[PlayerSerialNum];
	else												return nullptr;
}

UButton* UCharacterPickState::GetMyMeleeBorder() const
{
	if (MeleeButtons.IsValidIndex(PlayerSerialNum))	return MeleeButtons[PlayerSerialNum];
	else											return nullptr;
}

UButton* UCharacterPickState::GetMyRangeBorder() const
{
	if (RangeButtons.IsValidIndex(PlayerSerialNum))	return RangeButtons[PlayerSerialNum];
	else											return nullptr;
}

void UCharacterPickState::GoToDetail()
{
	if(ASelectCharacterController* Controller = Cast<ASelectCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))  )
	{
		Controller->SetDetailWidgetVisibility(true);
	}
}
