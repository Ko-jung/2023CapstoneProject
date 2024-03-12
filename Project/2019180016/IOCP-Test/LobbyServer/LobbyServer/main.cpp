#include "../../Common/Define.h"
#include "LobbyServer.h"

int main()
{
	std::wcout.imbue(std::locale("korean"));

	LobbyServer* server = new LobbyServer();

	server->Init(std::thread::hardware_concurrency());
	server->BindListen(8000);
	server->StartServer();
	server->ThreadJoin();
}