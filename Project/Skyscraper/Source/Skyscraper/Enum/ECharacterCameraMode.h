#pragma once

UENUM()
enum class ECharacterCameraMode
{
	ECCM_FollowController,	// ĳ���� ������ ��Ʈ�ѷ� ���󰡵��� (FPS)
	ECCM_SeparateController, // ĳ���� ����� ��Ʈ�ѷ� ���� ���� (RPG), (�ü��� ���ư����� �� �� ���)
};