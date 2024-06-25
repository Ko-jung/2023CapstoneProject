#pragma once

UENUM()
enum class ELoginResult : int8
{
	Success = 0,
	DatabaseError = -1,
	IDError = 1,
	PasswordError = 2,
};