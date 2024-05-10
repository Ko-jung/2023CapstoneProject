#include "CharacterPickState.h"

#include "Components/Button.h"
#include "../Core/SelectCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Skyscraper/SkyscraperGameMode.h"

// Fill out your copyright notice in the Description page of Project Settings.

void UCharacterPickState::NativeConstruct()
{
	Super::NativeConstruct();

	MyCharacterButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
	MyMeleeButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);
	MyRangeButton->OnClicked.AddUniqueDynamic(this, &ThisClass::GoToDetail);

 	auto gamemode = UGameplayStatics::GetGameMode(this);
	Gamemode = static_cast<ASkyscraperGameMode*>(gamemode);

	IsInfoChanged = false;

	FriendlyChracters.Add(FriendlyCharacter0);
	FriendlyChracters.Add(FriendlyCharacter1);
	FriendlyChracters.Add(FriendlyCharacter2);

	FriendlyMelee.Add(FriendlyMelee0);
	FriendlyMelee.Add(FriendlyMelee1);
	FriendlyMelee.Add(FriendlyMelee2);

	FriendlyRange.Add(FriendlyRange0);
	FriendlyRange.Add(FriendlyRange1);
	FriendlyRange.Add(FriendlyRange2);
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
	bool IsRight = Gamemode->GetSerialNum() >= MAXPLAYER / 2;


	for (int i = 0; i < PlayerSelectInfos.Num() / 2; i++)
	{
		int num = i + IsRight * MAXPLAYER / 2;
		auto CharacterNum = PlayerSelectInfos[num]->PickedCharacter;
		auto MeleeWeaponNum = PlayerSelectInfos[num]->PickedMeleeWeapon;
		auto RangeWeaponNum = PlayerSelectInfos[num]->PickedRangeWeapon;

		// Set Character portrait
		if (CharacterNum == ECharacterSelect::ECS_Null)
		{
			FriendlyChracters[i]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			FriendlyChracters[i]->SetBrushFromTexture(*CharacterImages.Find(CharacterNum));
		}

		// Set Melee Weapon portrait
		if (MeleeWeaponNum == EMeleeSelect::EMS_NONE)
		{
			FriendlyMelee[i]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			FriendlyMelee[i]->SetBrushFromTexture(*MeleeImages.Find(MeleeWeaponNum));
		}

		// Set Melee Weapon portrait
		if (RangeWeaponNum == ERangeSelect::ERS_NONE)
		{
			FriendlyRange[i]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			FriendlyRange[i]->SetBrushFromTexture(*RangeImages.Find(RangeWeaponNum));
		}
	}
}

void UCharacterPickState::GoToDetail()
{
	if(ASelectCharacterController* Controller = Cast<ASelectCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))  )
	{
		Controller->SetDetailWidgetVisibility(true);
	}
}
