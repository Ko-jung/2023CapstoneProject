#pragma once

UENUM()
enum class ECharacterCameraMode
{
	ECCM_FollowController,	// 캐릭터 방향이 컨트롤러 따라가도록 (FPS)
	ECCM_SeparateController, // 캐릭터 방향과 컨트롤러 방향 별개 (RPG), (시선만 돌아가도록 할 때 사용)
};