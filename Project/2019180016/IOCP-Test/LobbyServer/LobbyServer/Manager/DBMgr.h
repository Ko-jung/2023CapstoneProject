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
	���� Ÿ��:
	SQLINTEGER: �Ϲ������� 32��Ʈ ������ ���Ǵ� ODBC ���� Ÿ���Դϴ�. Ư�� �÷��������� int�� ������ ũ�⸦ �����ϴ�.
	SQLSMALLINT: �Ϲ������� 16��Ʈ ������ ���Ǵ� ODBC ���� Ÿ���Դϴ�. Ư�� �÷��������� short�� ������ ũ�⸦ �����ϴ�.
	SQLUINTEGER: ��ȣ ���� 32��Ʈ ������ ���Ǵ� ODBC ���� Ÿ���Դϴ�.
	SQLUSMALLINT: ��ȣ ���� 16��Ʈ ������ ���Ǵ� ODBC ���� Ÿ���Դϴ�.

	�ε� �Ҽ��� Ÿ��:
	SQLREAL: �ε� �Ҽ��� ��(�̱� ��������)�� ��Ÿ���� ODBC Ÿ���Դϴ�.
	SQLDOUBLE: �ε� �Ҽ��� ��(���� ��������)�� ��Ÿ���� ODBC Ÿ���Դϴ�.

	���ڿ� Ÿ��:
	SQLCHAR: ���� ���� Ÿ���� ��Ÿ���� ODBC Ÿ���Դϴ�. �Ϲ������� ���ڿ��� ��Ÿ���� �� ���˴ϴ�.
	SQLVARCHAR: ���� ���� ���ڿ��� ��Ÿ���� ODBC Ÿ���Դϴ�.
	SQLWCHAR: �����ڵ� ���� Ÿ���� ��Ÿ���� ODBC Ÿ���Դϴ�.
	SQLWVARCHAR: ���� ���� �����ڵ� ���ڿ��� ��Ÿ���� ODBC Ÿ���Դϴ�.

	������ Ÿ�� Ÿ��:
	SQL_DATE: ��¥ ���� ��Ÿ���� ODBC Ÿ���Դϴ�.
	SQL_TIME: �ð� ���� ��Ÿ���� ODBC Ÿ���Դϴ�.
	SQL_TIMESTAMP: ��¥ �� �ð� ���� ��Ÿ���� ODBC Ÿ���Դϴ�.

	��Ÿ Ÿ��:
	SQL_BINARY: ���� �����͸� ��Ÿ���� ODBC Ÿ���Դϴ�.
	SQL_BIT: ��Ʈ(0 �Ǵ� 1) ���� ��Ÿ���� ODBC Ÿ���Դϴ�.
*/

/*
	���� Ÿ��:
	SQL_C_SLONG: SQL_INTEGER�� ���εǴ� 32��Ʈ ��ȣ �ִ� ���� ������ Ÿ���Դϴ�.
	SQL_C_SHORT: SQL_SMALLINT�� ���εǴ� 16��Ʈ ��ȣ �ִ� ���� ������ Ÿ���Դϴ�.
	SQL_C_SSHORT: SQL_SMALLINT�� ���εǴ� 16��Ʈ ��ȣ �ִ� ���� ������ Ÿ���Դϴ�.
	SQL_C_LONG: SQL_INTEGER�� ���εǴ� 32��Ʈ ��ȣ �ִ� ���� ������ Ÿ���Դϴ�.
	SQL_C_SLONG: SQL_INTEGER�� ���εǴ� 32��Ʈ ��ȣ �ִ� ���� ������ Ÿ���Դϴ�.
	SQL_C_TINYINT: SQL_TINYINT�� ���εǴ� 8��Ʈ ��ȣ �ִ� ���� ������ Ÿ���Դϴ�.

	�ε� �Ҽ��� Ÿ��:
	SQL_C_FLOAT: SQL_FLOAT�� ���εǴ� �ε� �Ҽ��� ������ Ÿ���Դϴ�.
	SQL_C_DOUBLE: SQL_DOUBLE�� ���εǴ� ���� �������� �ε� �Ҽ��� ������ Ÿ���Դϴ�.

	���ڿ� Ÿ��:
	SQL_C_CHAR: SQL_CHAR�� ���εǴ� ���ڿ� ������ Ÿ���Դϴ�.
	SQL_C_BINARY: SQL_BINARY�� ���εǴ� ���� ������ Ÿ���Դϴ�.
	SQL_C_WCHAR: SQL_WCHAR�� ���εǴ� �����ڵ� ���ڿ� ������ Ÿ���Դϴ�.

	��¥ �� �ð� Ÿ��:
	SQL_C_DATE: SQL_DATE�� ���εǴ� ��¥ ������ Ÿ���Դϴ�.
	SQL_C_TIME: SQL_TIME�� ���εǴ� �ð� ������ Ÿ���Դϴ�.
	SQL_C_TIMESTAMP: SQL_TIMESTAMP�� ���εǴ� ��¥�� �ð� ������ Ÿ���Դϴ�.

	��Ÿ Ÿ��:
	SQL_C_BIT: SQL_BIT�� ���εǴ� ��Ʈ ������ Ÿ���Դϴ�.
	*/