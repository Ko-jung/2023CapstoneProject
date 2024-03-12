#include "../Common/Define.h"
#include "IOCPServer.h"

int main()
{
	setlocale(LC_ALL, "");
	std::wcout.imbue(std::locale(""));

	IOCPServer* IocpServer = new IOCPServer();

	// ���� CPU �ھŭ Worker thread ����
	IocpServer->Init(std::thread::hardware_concurrency());
	IocpServer->BindListen(8000);

	IocpServer->StartServer();

	IocpServer->ThreadJoin();
}