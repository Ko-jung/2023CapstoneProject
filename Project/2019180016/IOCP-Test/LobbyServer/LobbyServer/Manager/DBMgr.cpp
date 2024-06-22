#include "DBMgr.h"

DBMgr::DBMgr()
{ // Allocate environment handle  
    int retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &Henv);

    // Set the ODBC version environment attribute  
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        std::cout << "SQLAllocHandle OK" << std::endl;
        retcode = SQLSetEnvAttr(Henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);

        // Allocate connection handle  
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            std::cout << "SQLSetEnvAttr OK" << std::endl;
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, Henv, &Hdbc);

            // Set login timeout to 5 seconds  
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                std::cout << "SQLAllocHandle OK" << std::endl;
                SQLSetConnectAttr(Hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

                // Connect to data source  
                retcode = SQLConnect(Hdbc, (SQLWCHAR*)L"CapstoneProject", SQL_NTS, (SQLWCHAR*)NULL, 0, NULL, 0);

                // Allocate statement handle  
                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                    std::cout << "SQLConnect OK" << std::endl;
                    retcode = SQLAllocHandle(SQL_HANDLE_STMT, Hdbc, &Hstmt);
                }
            }
        }
    }
}

DBMgr::~DBMgr()
{
    SQLCancel(Hstmt);
    SQLFreeHandle(SQL_HANDLE_STMT, Hstmt);
    SQLDisconnect(Hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, Hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, Henv);
}

void DBMgr::PrintErr(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode)
{
    SQLSMALLINT iRec = 0;
    SQLINTEGER  iError;
    WCHAR wszMessage[1000];
    WCHAR wszState[SQL_SQLSTATE_SIZE + 1];
    if (RetCode == SQL_INVALID_HANDLE) {
        fwprintf(stderr, L"Invalid handle!\n");
        return;
    }
    while (SQLGetDiagRec(hType, hHandle, ++iRec, wszState, &iError, wszMessage,
        (SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)), (SQLSMALLINT*)NULL) == SQL_SUCCESS) {
        // Hide data truncated..
        if (wcsncmp(wszState, L"01004", 5)) {
            fwprintf(stderr, L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
        }
    }
}

int DBMgr::ExecLogin(const wchar_t* Query, const PTryLogin& TargetInfo)
{
    SQLRETURN ret;

    ret = SQLExecDirect(Hstmt, (SQLWCHAR*)Query, SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        PrintErr(Hstmt, SQL_NTS, ret);
        SQLCloseCursor(Hstmt);
    }


    SQLWCHAR ID[IDSIZE], Password[PASSWORDSIZE];
    SQLLEN CBID, CBPassword;
    ret = SQLBindCol(Hstmt, 1, SQL_C_WCHAR, ID, IDSIZE, &CBID);
    if (ret == SQL_ERROR)       PrintErr(Hstmt, SQL_BIND_TYPE, ret);
    ret = SQLBindCol(Hstmt, 2, SQL_C_WCHAR, ID, PASSWORDSIZE, &CBPassword);
    if (ret == SQL_ERROR)       PrintErr(Hstmt, SQL_BIND_TYPE, ret);

    for (int i = 0; ; i++)
    {
        ret = SQLFetch(Hstmt);
        if (ret == SQL_ERROR)   continue; 
        if (ret == SQL_NO_DATA) break;
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
        {
            // Fetch Succ

            // Input Info
            std::string IDString{ TargetInfo.ID };
            std::wstring TargetID{IDString.begin(), IDString.end() };

            std::string PasswordString{ TargetInfo.Password };
            std::wstring TargetPassword{ IDString.begin(), IDString.end() };

            // Database Info
            std::wstring IDWString = EraseEndBlank(ID);
            std::wstring PasswordWString = EraseEndBlank(Password);

            if (TargetID == IDWString)
            {
                if (TargetPassword == PasswordWString)
                {
                    // Succ
                    if (TargetInfo.IsRegister)
                    {
                        // INSTERT Query

                    }
                    else
                    {
                        return (char)ELoginResult::Success;
                    }
                }
                else
                {
                    // Password Error
                    return (char)ELoginResult::PasswordError;
                }
            }
            else
            {
                // ID Error
                return (char)ELoginResult::IDError;
            }
        }
        else
        {
            SQLCloseCursor(Hstmt);
            return (char)ELoginResult::DatabaseError;
        }
    }
    SQLCloseCursor(Hstmt);
    return (char)ELoginResult::DatabaseError;
}

std::wstring DBMgr::EraseEndBlank(const SQLWCHAR* TargetWchar)
{
    std::wstring ReturnWString{ TargetWchar };
    auto end = ReturnWString.find_last_not_of(L' ');
    if (end == std::wstring::npos) ReturnWString = L"";
    else ReturnWString = ReturnWString.substr(0, end + 1);

    return ReturnWString;
}
