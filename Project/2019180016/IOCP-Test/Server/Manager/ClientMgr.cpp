#include "ClientMgr.h"
#include "../ClientInfo.h"

#include "TimerMgr.h"

ClientMgr::ClientMgr() : 
	m_iClientId(0),
	m_iClientCount(0)
{
	for (auto& c : m_Clients)
	{
		c = new ClientInfo();
	}
}

void ClientMgr::Disconnect(int id)
{
	if (id < 0) return;		// INIT이 호출되어 id가 -1이 될 경우가 있음

	cout << "[" << id << "] Disconnect\n";
	m_Clients[id]->Init();
	m_iClientCount--;

	//PDisconnect PD;
	//m_Clients[id]->SendProcess(PD.PacketSize, &PD);

	// Process On ClientMgr::Init()
	//m_Clients[id]->Init();
	//m_iClientCount--;
}

void ClientMgr::Init(int id)
{
	m_Clients[id]->Init();
	m_iClientCount--;
}

void ClientMgr::Send(int id, Packet* p, int size)
{
	m_Clients[id]->SendProcess(size, p);
}

void ClientMgr::SendPacketToAllSocketsInRoom(int roomId, Packet* p, int packetSize)
{
	for (int i = 0; i < MAXPLAYER; i++)
	{
		SOCKET s = m_Clients[roomId * MAXPLAYER + i]->GetSocket();

		if (s != INVALID_SOCKET)
		{
			m_Clients[roomId * MAXPLAYER + i]->SendProcess(packetSize, p);
		}
	}
}

void ClientMgr::Recv(int id, const DWORD& bytes, EXP_OVER* exp)
{
	m_Clients[id]->RecvProcess(bytes, exp);
}

ClientInfo* ClientMgr::GetEmptyClient()
{
	auto it = std::find_if(m_Clients.begin(), m_Clients.end(), [](ClientInfo* a) {return a->GetClientNum() == -1; });
	if (it != m_Clients.end())
	{
		return *it;
	}
	else
	{
		return nullptr;
	}
}

ClientInfo* ClientMgr::GetEmptyClient(int& clientNum)
{
	for (int i = 0; i < m_Clients.size(); i++)
	{
		if (m_Clients[i]->GetClientNum() == -1)
		{
			clientNum = i;
			m_iClientCount++;
			return m_Clients[i];
		}
	}
	return nullptr;
}

void ClientMgr::SendPacketToAllExceptSelf(int id, Packet* p, int packetSize)
{
	int RoomNum = id / MAXPLAYER;
	for (int i = 0; i < MAXPLAYER; i++)
	{
		if (m_Clients[RoomNum * MAXPLAYER + i]->GetSocket() == INVALID_SOCKET
			//|| m_Clients[RoomNum * MAXPLAYER + i]->ClientNum == -1
			|| RoomNum * MAXPLAYER + i == id)
		{
			continue;
		}

		m_Clients[RoomNum * MAXPLAYER + i]->SendProcess(packetSize, p);
	}
}

void ClientMgr::SendPacketToAllience(int id, Packet* p, int packetSize)
{
	int RoomNum = id / MAXPLAYER;
	bool IsTeamA = (id % MAXPLAYER) < (MAXPLAYER / 2);
	for (int i = 0; i < MAXPLAYER / 2; i++)
	{
		int NowIndex = RoomNum * MAXPLAYER + i + (!IsTeamA) * (MAXPLAYER / 2);	// 0 or 3
		if (m_Clients[NowIndex]->GetSocket() == INVALID_SOCKET)
		{
			continue;
		}

		m_Clients[NowIndex]->SendProcess(packetSize, p);
	}
}

void ClientMgr::SendOldPlayerList(int id)
{
	int RoomNum = id / MAXPLAYER;
	PJoinPlayerInSkillTest NewPlayer;
	for (int i = 0; i < MAXPLAYER; i++)
	{
		if (m_Clients[RoomNum * MAXPLAYER + i]->GetSocket() == INVALID_SOCKET
			|| RoomNum * MAXPLAYER + i == id) continue;

		NewPlayer.ClientNum = i;
		m_Clients[id]->SendProcess(NewPlayer.PacketSize, &NewPlayer);
	}
}

bool ClientMgr::CheckSelectDuplication(int id, ECharacter c)
{
	int roomNum = id / MAXPLAYER;
	int clientNum = id % MAXPLAYER;

	int temp = MAXPLAYER;

	if (clientNum < temp / 2)
	{
		for (int i = 0; i < temp / 2; i++)
		{
			if (m_Clients[roomNum * temp + i]->GetECharacter() == c)
			{
				return true;
			}
		}
	}
	else
	{
		for (int i = temp / 2; i < temp; i++)
		{
			if (m_Clients[roomNum * temp + i]->GetECharacter() == c)
			{
				return true;
			}
		}
	}

	return false;
}

bool ClientMgr::CheckFallDie(int id, PPlayerPosition PPP)
{
	if ((m_Clients[id]->GetState() == ECharacterState::LIVING) && (PPP.Location.Z < -(9000.f + 500.f)))
	{
		return true;
	}
	return false;
}

void ClientMgr::ProcessMove(int id, PPlayerPosition PPP)
{
	SendPacketToAllExceptSelf(id, &PPP, sizeof(PPP));
	//CheckFallDie(id, PPP);
}

void ClientMgr::ChangeState(int id, ECharacterState state)
{
	m_Clients[id]->SetState(state);
}

void ClientMgr::ProcessItem(int id, PUseItem PUI)
{
	int Timer = 0;
	switch ((EItemEffect)PUI.Effect)
	{
	case EItemEffect::Team_PlusHealth:
	case EItemEffect::Team_Power:
	case EItemEffect::Team_Speed:
	{
		bool IsTeamB = (id % MAXPLAYER) > (MAXPLAYER / 2);
		for (int i = 0; i < MAXPLAYER / 2; i++)
		{
			PUI.UsePlayerSerial = i + IsTeamB * (MAXPLAYER / 2);
			SendPacketToAllSocketsInRoom(id, &PUI, sizeof(PUI));
		}
	}
	break;
	case EItemEffect::Single_BoostBulletInfinity:
	case EItemEffect::Single_GodMode:
	case EItemEffect::Gravity_Up:
	case EItemEffect::Gravity_Down:
		SendPacketToAllSocketsInRoom(id, &PUI, sizeof(PUI));
		break;
	case EItemEffect::Tile_Break:
		// 위치 선택 UI 제작되면 제작
		SendPacketToAllSocketsInRoom(id, &PUI, sizeof(PUI));
		break;
	default:
		break;
	}

	// TODO: 서버에서 버프를 꺼야한다.
	
	// TimerEvent OffTimer{std::chrono::seconds(Timer),
	// std::bind(&)};
	// TimerMgr::Instance()->Insert
}

void ClientMgr::ProcessShieldSphereHeal(int id, PSkillInteract PSI)
{
	if (m_Clients[id]->IsOverlappedShieldSphere)
	{
		m_Clients[id]->IsOverlappedShieldSphere = false;
	}
	else
	{
		m_Clients[id]->IsOverlappedShieldSphere = true;

		TimerEvent TE(std::chrono::seconds(1),
			std::bind(&ClientMgr::ShieldSphereHeal, this, id));
		TimerMgr::Instance()->Insert(TE);
	}
}

float ClientMgr::ProcessShieldDamaged(int id, PDamagedSkillActor PDSA, float Damage)
{
	int RoomId = id / MAXPLAYER;
	bool IsBreak = m_Clients[RoomId * MAXPLAYER + PDSA.SkillActorOwner]->TakeDamageToShield(Damage);

	if(IsBreak)
	{
		m_Clients[RoomId * MAXPLAYER + PDSA.SkillActorOwner]->ShieldHp = 1500.f;
		return 0.f;
	}
	else
	{
		return m_Clients[RoomId * MAXPLAYER + PDSA.SkillActorOwner]->ShieldHp;
	}


	/*int ShieldId{ -1 };
	for (int i = 0; i < MAXPLAYER; i++)
	{
		if (m_Clients[RoomId * MAXPLAYER + i]->SelectInfo == ECharacter::Shield)
		{
			ShieldId = RoomId * MAXPLAYER + i;
		}
	}

	if (ShieldId != -1)
	{
		m_Clients[RoomId * MAXPLAYER + PDSA.SkillActorOwner]->TakeDamageToShield(Damage);
	}
	else
	{
		cout << "[" << RoomId << "] Room has no Shield Character" << endl;
	}*/
}

void ClientMgr::Heal(int id, float HealAmount)
{
	m_Clients[id]->Heal(HealAmount);
}

void ClientMgr::ItemHeal(int id, EItemRareLevel level)
{
	bool IsTeamA = id < MAXPLAYER / 2;
	int RoomNum = id / MAXPLAYER;
	float HealCount{ 0 };
	switch (level)
	{
	case EItemRareLevel::Normal:	HealCount = 250.f;	break;
	case EItemRareLevel::Rare:		HealCount = 500.f;	break;
	case EItemRareLevel::Legend:	HealCount = 1000.f;	break;
	default:
		break;
	}

	for (int i = 0; i < MAXPLAYER / 2; i++)
	{
		// 방번호 0 * 6 + [0, 2] + 0 or 3
		int TargetId = RoomNum * MAXPLAYER + i + (MAXPLAYER / 2 * IsTeamA);
		Heal(TargetId, HealCount);
	}

	for (int i = 0; i < MAXPLAYER; i++)
	{
		int TargetId = RoomNum * MAXPLAYER + i;

		PChangedPlayerHP PCPH(TargetId, m_Clients[TargetId]->GetCurrnetHp());
		SendPacketToAllSocketsInRoom(RoomNum, &PCPH, sizeof(PCPH));
	}
}

void ClientMgr::ShieldSphereHeal(int id)
{
	if (m_Clients[id]->IsOverlappedShieldSphere)
	{
		float HealAmount = (m_Clients[id]->GetECharacter() == ECharacter::Shield) ? 100 : 50;
		Heal(id, HealAmount);

		TimerEvent TE(std::chrono::seconds(1),
			std::bind(&ClientMgr::ShieldSphereHeal, this, id));
		TimerMgr::Instance()->Insert(TE);

		cout << "[" << id << "] Client \""<< HealAmount << "\" Healed By Shield Sphere" << endl;

		PChangedPlayerHP PCPH;
		PCPH.AfterHP = m_Clients[id]->CurrentHp;
		PCPH.ChangedPlayerSerial = id % MAXPLAYER;
		Send(id, &PCPH, PCPH.PacketSize);
	}
}
