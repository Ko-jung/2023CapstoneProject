// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/MainGame/Interface/Item/ItemInteraction.h"
#include "Item_Root.generated.h"

class UTextRenderComponent;
class UWidgetComponent;
class USphereComponent;

UCLASS()
class SKYSCRAPER_API AItem_Root : public AActor, public IItemInteraction
{
	GENERATED_BODY()

	// 오버랩 범위 SphereComponent
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
	// 상호작용 게이지 Widget Component
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> GaugeWidgetComponent;
	// Text Render
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	// 상호작용 필요 시간
	UPROPERTY(EditAnywhere)
	float RequiredTime;
	// 현재 상호작용 시간
	UPROPERTY()
	float CurrentInteractionTime;
	// 가장 이전 상호작용 시간
	UPROPERTY()
	float LastInteractionTime;
	// Player - Widget 맵
	UPROPERTY()
	TMap<AActor*, UUserWidget*> PlayerAndWidgetMap;
	// 현재 상호작용 중인 캐릭터
	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractionActor;

	// 상호작용 키 위젯
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WBP_InteractionKey;
	
public:	
	// 생성자
	AItem_Root();

protected:
	// Begin Play
	virtual void BeginPlay() override;
	// End Play
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	virtual void DoItemEffect(){};
public:	
	// Tick Event
	virtual void Tick(float DeltaTime) override;
	// 인터페이스 - 상호작용 키를 통한 상호작용 시 실행될 함수
	virtual void ItemInteraction(const AActor* InteractionActor) override;
};
