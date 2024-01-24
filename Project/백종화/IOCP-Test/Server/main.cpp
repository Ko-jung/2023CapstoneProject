#include "Define.h"
#include "IOCPServer.h"

int main()
{
	setlocale(LC_ALL, "");
	std::wcout.imbue(std::locale(""));

	IOCPServer* IocpServer = new IOCPServer();

	// 현재 CPU 코어만큼 Worker thread 생성
	IocpServer->Init(std::thread::hardware_concurrency());
	IocpServer->BindListen(8000);

	IocpServer->StartServer();

	IocpServer->ThreadJoin();
}