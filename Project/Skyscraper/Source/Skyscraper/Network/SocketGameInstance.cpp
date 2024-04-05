// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketGameInstance.h"
#include "../../../../Common/Packet.h"


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
		PPlayerSelectInfo* PPS1 = new PPlayerSelectInfo{ ECharacter::Assassin, EMeleeWeapon::Dagger, ERangeWeapon::AssaultRifle, 0 };
		PPlayerSelectInfo* PPS2 = new PPlayerSelectInfo{ ECharacter::Boomerang, EMeleeWeapon::Greatsword, ERangeWeapon::SubmachineGun, 1 };
		PPlayerSelectInfo* PPS3 = new PPlayerSelectInfo{ ECharacter::Detector, EMeleeWeapon::Katana, ERangeWeapon::GrenadeLauncher, 2 };
	
		PPlayerSelectInfo* PPS4 = new PPlayerSelectInfo{ ECharacter::Elect, EMeleeWeapon::Dagger, ERangeWeapon::AssaultRifle, 3 };
		PPlayerSelectInfo* PPS5 = new PPlayerSelectInfo{ ECharacter::Shield, EMeleeWeapon::Greatsword, ERangeWeapon::GrenadeLauncher, 4 };
		PPlayerSelectInfo* PPS6 = new PPlayerSelectInfo{ ECharacter::Wind, EMeleeWeapon::Katana, ERangeWeapon::SubmachineGun, 5 };

		SelectInfo.Add(PPS1);
		SelectInfo.Add(PPS2);
		SelectInfo.Add(PPS3);

		SelectInfo.Add(PPS4);
		SelectInfo.Add(PPS5);
		SelectInfo.Add(PPS6);
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
