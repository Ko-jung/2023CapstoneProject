// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterController.h"

#include "../UI/SelectCharacter.h"
#include "../UI/SelectDetail.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


ASelectCharacterController::ASelectCharacterController()
{
    { // 위젯 에셋 불러오기
        static ConstructorHelpers::FClassFinder<USelectCharacter> SelectCharacterWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/SelectCharacter/WidgetUI/WBP_SelectCharacter.WBP_SelectCharacter_C'"));
        UE_LOG(LogTemp, Warning, TEXT("why00"));
        if(SelectCharacterWidgetAsset.Succeeded())
        {

            UE_LOG(LogTemp, Warning, TEXT("why01"));
            CharacterSelectionWidgetClass = SelectCharacterWidgetAsset.Class;
        }

        ///Script/UMGEditor.WidgetBlueprint
        static ConstructorHelpers::FClassFinder<USelectDetail> SelectDetailWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2019180031/SelectCharacter/WidgetUI/WBP_SelectDetail.WBP_SelectDetail_C'"));
        if (SelectDetailWidgetAsset.Succeeded())
        {
            UE_LOG(LogTemp, Warning, TEXT("why02"));
            SelectDetailWidgetClass = SelectDetailWidgetAsset.Class;
        }
    }
}

void ASelectCharacterController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("input0"));

    { // 캐릭터 픽창 위젯 생성 및 뷰포트 추가
        if (CharacterSelectionWidgetClass)
        {
            CharacterSelectionWidget = Cast<USelectCharacter>(CreateWidget(this, CharacterSelectionWidgetClass));
            UE_LOG(LogTemp, Warning, TEXT("input1"));
            if(CharacterSelectionWidget)
            {
                UE_LOG(LogTemp, Warning, TEXT("input2"));
                CharacterSelectionWidget->AddToViewport();
            }
        }
    }

    { // 디테일 창 위젯 생성
	    if(SelectDetailWidgetClass)
	    {
            SelectDetailWidget = Cast<USelectDetail>(CreateWidget(this, SelectDetailWidgetClass));
	    }
    }

    { // 인풋모드 설정 및 커서 가시성 설정
        SetInputMode(FInputModeGameAndUI());
        SetShowMouseCursor(true);
    }
    
        
}

void ASelectCharacterController::SetDetailWidgetVisibility(bool bVisible) const
{
    if(bVisible)
    {
        CharacterSelectionWidget->RemoveFromParent();
        SelectDetailWidget->AddToViewport();
    }
    else
    {
        SelectDetailWidget->RemoveFromParent();
        CharacterSelectionWidget->AddToViewport();
        
    }
}
