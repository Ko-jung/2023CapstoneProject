// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Skyscraper/Network/LobbyMode.h"
#include "Skyscraper/MainGame/Core/SkyscraperPlayerController.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Skyscraper/MainGame/Widget/Combat/MainCombatWidget.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool ULobbyWidget::Initialize()
{
	bool Succ = Super::Initialize();
	if (!Succ) return false;

	IsMatching = false;
	MatchingBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnMatchingButtonClick);

	DaggerBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnDaggerButtonClick);
	KatanaBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnKatanaButtonClick);
	GreatSwordBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnGreatSwordButtonClick);

	SMGBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnSMGButtonClick);
	RifleBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnRifleButtonClick);
	RPGBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnRPGButtonClick);

	AssasinBtn->OnClicked.AddDynamic(this,	&ULobbyWidget::OnAssasinButtonClick);
	BoomerangBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnBoomerangButtonClick);
	ElectricBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnElectricButtonClick);
	RadarBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnRadarButtonClick);
	ShieldBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnShieldButtonClick);
	WindBtn->OnClicked.AddDynamic(this, &ULobbyWidget::OnWindButtonClick);

	MatchingTimer->SetVisibility(ESlateVisibility::Hidden);

	LobbyGameMode = Cast<ALobbyMode>(GetWorld()->GetAuthGameMode());

	// Now Gamemode Is ALobbyMode?
	return (bool)LobbyGameMode;
}

void ULobbyWidget::SpawnNewCharacter(ECharacterSelect ECharacter)
{
	APawn* PrevPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTransform PrevCharacterTransform = PrevPawn->GetActorTransform();

	ASkyscraperCharacter* Character = GetWorld()->SpawnActorDeferred<ASkyscraperCharacter>(
		Characters[ECharacter],
		PrevCharacterTransform);

	if (Character)
	{
		ASkyscraperPlayerController* Controller = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
		if (Controller)
		{
			Controller->Possess(Character);
			Controller->SetPossessingPawn();
		}
		PrevPawn->Destroy();
		Character->FinishSpawning(PrevCharacterTransform);
		UE_LOG(LogTemp, Warning, TEXT("ECS_ElectricCharacter Spawned"));

		Controller->GetMainCombatWidget()->SetCharacterImage(ECharacter);
		Controller->GetMainCombatWidget()->InitCoolTime();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ULobbyWidget::SpawnNewCharacter() Character is nullptr. ECharacterSelect is %d"), ECharacter);
	}
}

void ULobbyWidget::OnMatchingButtonClick()
{
	PlayButtonOnClickSound();

	UE_LOG(LogTemp, Warning, TEXT("ULobbyWidget::OnMatchingButtonClick()"));

	LobbyGameMode->Ready(IsMatching);
	if (IsMatching)
	{
		MatchingTimer->SetVisibility(ESlateVisibility::Hidden);
		FString String = TEXT("매칭 시작");
		MatchingText->SetText(FText::FromString(String));
		IsMatching = false;
	}
	else
	{
		MatchingStartTime = FDateTime::Now();
		MatchingTimer->SetVisibility(ESlateVisibility::HitTestInvisible);
		FString String = TEXT("매칭 종료");
		MatchingText->SetText(FText::FromString(String));
		IsMatching = true;
	}
}

void ULobbyWidget::OnDaggerButtonClick()
{
	ASkyscraperPlayerController* Controller = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangePlayerMeleeWeapon(EMeleeSelect::EMS_Dagger);
}

void ULobbyWidget::OnKatanaButtonClick()
{
	ASkyscraperPlayerController* Controller = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangePlayerMeleeWeapon(EMeleeSelect::EMS_Katana);
}

void ULobbyWidget::OnGreatSwordButtonClick()
{
	ASkyscraperPlayerController* Controller = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangePlayerMeleeWeapon(EMeleeSelect::EMS_GreatSword);
}

void ULobbyWidget::OnSMGButtonClick()
{
	ASkyscraperPlayerController* Controller = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangePlayerRangeWeapon(ERangeSelect::ERS_SMG);
}

void ULobbyWidget::OnRifleButtonClick()
{
	ASkyscraperPlayerController* Controller = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangePlayerRangeWeapon(ERangeSelect::ERS_Rifle);
}

void ULobbyWidget::OnRPGButtonClick()
{
	ASkyscraperPlayerController* Controller = Cast<ASkyscraperPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangePlayerRangeWeapon(ERangeSelect::ERS_RPG);
}

void ULobbyWidget::OnAssasinButtonClick()
{
	SpawnNewCharacter(ECharacterSelect::ECS_AssassinCharacter);
}

void ULobbyWidget::OnBoomerangButtonClick()
{
	SpawnNewCharacter(ECharacterSelect::ECS_BoomerangCharacter);
}

void ULobbyWidget::OnElectricButtonClick()
{
	SpawnNewCharacter(ECharacterSelect::ECS_ElectricCharacter);
}

void ULobbyWidget::OnRadarButtonClick()
{
	SpawnNewCharacter(ECharacterSelect::ECS_DetectionCharacter);
}

void ULobbyWidget::OnShieldButtonClick()
{
	SpawnNewCharacter(ECharacterSelect::ECS_ShieldCharacter);
}

void ULobbyWidget::OnWindButtonClick()
{
	SpawnNewCharacter(ECharacterSelect::ECS_WindCharacter);
}

void ULobbyWidget::UpdateMatchingTimer()
{
	FDateTime NowTime = FDateTime::Now();
	FTimespan MatchingDelta = NowTime - MatchingStartTime;

	int DeltaSec = (int)MatchingDelta.GetTotalSeconds();

	int Minute = DeltaSec / 60;
	int Second = DeltaSec % 60;

	TCHAR Buffer[256];
	FCString::Sprintf(Buffer, TEXT("%02d : %02d"), Minute, Second);
	FString TimerString = FString(Buffer);
	//UE_LOG(LogClass, Warning, TEXT("ULobbyWidget::UpdateMatchingTimer() %s"), *TimerString);

	MatchingTimer->SetText(FText::FromString(TimerString));
}
