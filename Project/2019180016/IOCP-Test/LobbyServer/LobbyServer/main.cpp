#include "../../Common/Define.h"
#include "LobbyServer.h"

int main()
{
	std::locale::global(std::locale("Korean"));
	std::wcout.imbue(std::locale("korean"));

	LobbyServer* server = new LobbyServer();

	server->Init(std::thread::hardware_concurrency());
	server->BindListen(LOBBYSERVERPORT);
	server->StartServer();
	server->ThreadJoin();
}