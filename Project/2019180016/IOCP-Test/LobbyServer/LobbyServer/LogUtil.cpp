#include "../../Common/Define.h"
#include "LogUtil.h"

void LogUtil::error_display(int err_no)
{
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
}
