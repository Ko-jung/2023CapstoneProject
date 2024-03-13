#include "Define.h"
#include "LogUtil.h"

#include <iostream>

using std::cout;
using std::endl;

void LogUtil::error_display(int err_no)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, 0);
	std::wcout << lpMsgBuf << std::endl;
	//while (true);
	LocalFree(lpMsgBuf);
}

void LogUtil::error_display(const char* msg)
{
    WCHAR* lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    std::cout << msg;
    std::wcout << L" 에러 " << lpMsgBuf << std::endl;
    //while (true);
    // 디버깅 용
    LocalFree(lpMsgBuf);
}

void LogUtil::PrintLog(const char* s)
{
#ifdef _DEBUG
	cout << s << endl;
#endif // _DEBUG
}
