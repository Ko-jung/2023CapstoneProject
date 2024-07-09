// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketGameInstance.h"
#include "Packet.h"
#include "Skyscraper/Network/NetworkGameMode.h"


void USocketGameInstance::Init()
{
	//if (SelectInfo.IsEmpty())
	//{
	//	for (int i = 0; i < 6; i++)
	//	{
	//		SelectInfo.Add(new PPlayerSelectInfo());
	//	}
	//}
	SerialNum = 0;
	if (SelectInfo.IsEmpty())
	{
		PPlayerSelectInfo* PPS1 = new PPlayerSelectInfo{ ECharacterSelect::ECS_AssassinCharacter, EMeleeSelect::EMS_Dagger, ERangeSelect::ERS_Rifle, 0 };
		PPlayerSelectInfo* PPS2 = new PPlayerSelectInfo{ ECharacterSelect::ECS_BoomerangCharacter, EMeleeSelect::EMS_GreatSword, ERangeSelect::ERS_SMG, 1 };
		PPlayerSelectInfo* PPS3 = new PPlayerSelectInfo{ ECharacterSelect::ECS_DetectionCharacter, EMeleeSelect::EMS_Katana, ERangeSelect::ERS_RPG, 2 };
	
		PPlayerSelectInfo* PPS4 = new PPlayerSelectInfo{ ECharacterSelect::ECS_ElectricCharacter, EMeleeSelect::EMS_Dagger, ERangeSelect::ERS_Rifle, 3 };
		PPlayerSelectInfo* PPS5 = new PPlayerSelectInfo{ ECharacterSelect::ECS_ShieldCharacter, EMeleeSelect::EMS_GreatSword, ERangeSelect::ERS_RPG, 4 };
		PPlayerSelectInfo* PPS6 = new PPlayerSelectInfo{ ECharacterSelect::ECS_WindCharacter, EMeleeSelect::EMS_Katana, ERangeSelect::ERS_SMG, 5 };

		SelectInfo.Add(PPS1);
		SelectInfo.Add(PPS2);
		SelectInfo.Add(PPS3);

		SelectInfo.Add(PPS4);
		SelectInfo.Add(PPS5);
		SelectInfo.Add(PPS6);
	}
	else
	{
		for (int i = 0; i < MAXPLAYER; i++)
		{
			SelectInfo.Add(new PPlayerSelectInfo());
		}
	}
}

void USocketGameInstance::SetSelectInfo(TArray<PPlayerSelectInfo*> s)
{
	if (s.Num() == SelectInfo.Num())
	{
		for (int i = 0; i < s.Num(); i++)
		{
			SelectInfo[i] = s[i];
		}
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("s.Num() != SelectInfo.Num()"));
	}
}
