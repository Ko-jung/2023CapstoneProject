// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCombatWidget.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UMainCombatWidget::SetCharacterImage(ECharacterSelect CharacterType)
{
	if (CharacterType == ECharacterSelect::ECS_Null || CharacterType == ECharacterSelect::ECS_Count) return;

	if(CharacterTextures.IsValidIndex(static_cast<int>(CharacterType)) && CharacterTextures[static_cast<int>(CharacterType)])
	{
		CharacterImage->SetBrushFromTexture(CharacterTextures[static_cast<int>(CharacterType)]);
	}
}

void UMainCombatWidget::UseSkill(bool IsSpecial, float CoolTime)
{
	if (CoolTime < 0.f) return;

	if (IsSpecial)
	{
		SpecialSkillCurrentTime = SpecialSkillRequestTime = CoolTime;
	}
	else
	{
		CommonSkillCurrentTime = CommonSkillRequestTime = CoolTime;
	}
}

void UMainCombatWidget::UpdateProgressBar()
{
	CommonSkillProgressBar->SetPercent(UKismetMathLibrary::SafeDivide(CommonSkillCurrentTime, CommonSkillRequestTime));
	SpecialSkillProgressBar->SetPercent(UKismetMathLibrary::SafeDivide(SpecialSkillCurrentTime, SpecialSkillRequestTime));
}

void UMainCombatWidget::InitCoolTime()
{
	CommonSkillCurrentTime = SpecialSkillCurrentTime = 0.f;
}

void UMainCombatWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMainCombatWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (CommonSkillCurrentTime > 0.f)
	{
		CommonSkillCurrentTime -= InDeltaTime;
		if (CommonSkillCurrentTime < 0.f) CommonSkillCurrentTime = 0.f;
	}
	if (SpecialSkillCurrentTime > 0.f)
	{
		SpecialSkillCurrentTime -= InDeltaTime;
		if (SpecialSkillCurrentTime < 0.f) SpecialSkillCurrentTime = 0.f;
	}

	UpdateProgressBar();
}
