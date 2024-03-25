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

	bool IsRight = Gamemode->GetSerialNum() > MAXPLAYER / 2;
	for (int i = 0; i < PlayerSelectInfos.Num() / 2; i++)
	{
		int num = i + IsRight * MAXPLAYER / 2;
		auto CharacterNum = PlayerSelectInfos[num]->PickedCharacter;
		auto MeleeWeaponNum = PlayerSelectInfos[num]->PickedMeleeWeapon;
		auto RangeWeaponNum = PlayerSelectInfos[num]->PickedRangeWeapon;

		// Set Character portrait
		if (CharacterNum == ECharacter::NullCharacter)
		{
			FriendlyChracters[num]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			FriendlyChracters[num]->SetBrushFromTexture(CharacterImages[(int)CharacterNum]);
		}

		// Set Melee Weapon portrait
		if (MeleeWeaponNum == EMeleeWeapon::NullWeapon)
		{
			FriendlyMelee[num]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			FriendlyMelee[num]->SetBrushFromTexture(MeleeImages[(int)MeleeWeaponNum]);
		}

		// Set Melee Weapon portrait
		if (RangeWeaponNum == ERangeWeapon::NullWeapon)
		{
			FriendlyRange[num]->SetBrushFromTexture(QuestionImages);
		}
		else
		{
			FriendlyRange[num]->SetBrushFromTexture(RangeImages[(int)RangeWeaponNum]);
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
