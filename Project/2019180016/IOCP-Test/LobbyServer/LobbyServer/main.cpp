#include "../../Common/Define.h"
#include "LobbyServer.h"

int main()
{
	setlocale(LC_ALL, "");
	std::wcout.imbue(std::locale(""));

	LobbyServer* server = new LobbyServer();

	server->Init(std::thread::hardware_concurrency());
	server->BindListen(LOBBYSERVERPORT);
	server->StartServer();
	server->ThreadJoin();
}