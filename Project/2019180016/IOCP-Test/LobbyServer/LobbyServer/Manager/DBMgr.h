#pragma once
#include "../../../Common/Define.h"
#include "../../../../../Common/Packet.h"

#define UNICODE  
#include <windows.h>
#include <sqlext.h>

class DBMgr
{
public:
	SingleTon(DBMgr);

public:
	DBMgr();
	~DBMgr();
	
	void PrintErr(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode);

	int ExecLogin(const wchar_t* Query, const PTryLogin& TargetInfo);

	// UTIL
	static std::wstring EraseEndBlank(const SQLWCHAR* TargetWchar);

	SQLHENV Henv;
	SQLHDBC Hdbc;
	SQLHSTMT Hstmt = 0;
};

/*
	정수 타입:
	SQLINTEGER: 일반적으로 32비트 정수로 사용되는 ODBC 정수 타입입니다. 특정 플랫폼에서는 int와 동일한 크기를 갖습니다.
	SQLSMALLINT: 일반적으로 16비트 정수로 사용되는 ODBC 정수 타입입니다. 특정 플랫폼에서는 short와 동일한 크기를 갖습니다.
	SQLUINTEGER: 부호 없는 32비트 정수로 사용되는 ODBC 정수 타입입니다.
	SQLUSMALLINT: 부호 없는 16비트 정수로 사용되는 ODBC 정수 타입입니다.

	부동 소수점 타입:
	SQLREAL: 부동 소수점 값(싱글 프리시전)을 나타내는 ODBC 타입입니다.
	SQLDOUBLE: 부동 소수점 값(더블 프리시전)을 나타내는 ODBC 타입입니다.

	문자열 타입:
	SQLCHAR: 단일 문자 타입을 나타내는 ODBC 타입입니다. 일반적으로 문자열을 나타내는 데 사용됩니다.
	SQLVARCHAR: 가변 길이 문자열을 나타내는 ODBC 타입입니다.
	SQLWCHAR: 유니코드 문자 타입을 나타내는 ODBC 타입입니다.
	SQLWVARCHAR: 가변 길이 유니코드 문자열을 나타내는 ODBC 타입입니다.

	데이터 타임 타입:
	SQL_DATE: 날짜 값을 나타내는 ODBC 타입입니다.
	SQL_TIME: 시간 값을 나타내는 ODBC 타입입니다.
	SQL_TIMESTAMP: 날짜 및 시간 값을 나타내는 ODBC 타입입니다.

	기타 타입:
	SQL_BINARY: 이진 데이터를 나타내는 ODBC 타입입니다.
	SQL_BIT: 비트(0 또는 1) 값을 나타내는 ODBC 타입입니다.
*/

/*
	정수 타입:
	SQL_C_SLONG: SQL_INTEGER과 매핑되는 32비트 부호 있는 정수 데이터 타입입니다.
	SQL_C_SHORT: SQL_SMALLINT와 매핑되는 16비트 부호 있는 정수 데이터 타입입니다.
	SQL_C_SSHORT: SQL_SMALLINT와 매핑되는 16비트 부호 있는 정수 데이터 타입입니다.
	SQL_C_LONG: SQL_INTEGER와 매핑되는 32비트 부호 있는 정수 데이터 타입입니다.
	SQL_C_SLONG: SQL_INTEGER와 매핑되는 32비트 부호 있는 정수 데이터 타입입니다.
	SQL_C_TINYINT: SQL_TINYINT와 매핑되는 8비트 부호 있는 정수 데이터 타입입니다.

	부동 소수점 타입:
	SQL_C_FLOAT: SQL_FLOAT와 매핑되는 부동 소수점 데이터 타입입니다.
	SQL_C_DOUBLE: SQL_DOUBLE와 매핑되는 더블 프리시전 부동 소수점 데이터 타입입니다.

	문자열 타입:
	SQL_C_CHAR: SQL_CHAR와 매핑되는 문자열 데이터 타입입니다.
	SQL_C_BINARY: SQL_BINARY와 매핑되는 이진 데이터 타입입니다.
	SQL_C_WCHAR: SQL_WCHAR와 매핑되는 유니코드 문자열 데이터 타입입니다.

	날짜 및 시간 타입:
	SQL_C_DATE: SQL_DATE와 매핑되는 날짜 데이터 타입입니다.
	SQL_C_TIME: SQL_TIME와 매핑되는 시간 데이터 타입입니다.
	SQL_C_TIMESTAMP: SQL_TIMESTAMP와 매핑되는 날짜와 시간 데이터 타입입니다.

	기타 타입:
	SQL_C_BIT: SQL_BIT와 매핑되는 비트 데이터 타입입니다.
	*/