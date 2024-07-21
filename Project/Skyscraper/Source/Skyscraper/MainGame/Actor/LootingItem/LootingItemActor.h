// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/Enum/EItemEffect.h"
#include "Skyscraper/Enum/EItemRareLevel.h"
#include "Skyscraper/MainGame/Interface/Item/ItemInteraction.h"
#include "LootingItemActor.generated.h"

class ASkyscraperCharacter;
class UProgressBar;
class UTextRenderComponent;
class UWidgetComponent;
class USphereComponent;

UCLASS()
class SKYSCRAPER_API ALootingItemActor : public AActor, public IItemInteraction
{
	GENERATED_BODY()

public:
	// 생성자
	ALootingItemActor();


protected:
	// Begin Play
	virtual void BeginPlay() override;
	
	// End Play
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// 상호작용 완료시 해당 캐릭터에게 아이템을 추가하는 함수
	UFUNCTION()
		virtual void AddItemToUsedCharacter(ASkyscraperCharacter* ItemUsedCharacter);

	// Begin Overlap - SphereComponent
	UFUNCTION()
		void SphereBeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	// End Overlap - SphereComponent
	UFUNCTION()
		void SphereEndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);

	// End Overlap시 플레이어의 위젯을 제거하는 함수
	void RemovePlayerWidget(AActor* EndOverlapCharacter);

	// 프로그레스 바의 퍼센트를 바꾸는 함수
	virtual void SetProgressBarPercent() const;
public:
	// Tick Event
	virtual void Tick(float DeltaTime) override;
	// 인터페이스 - 상호작용 키를 통한 상호작용 시 실행될 함수
	virtual void ItemInteraction(AActor* InteractionActor) override;

	// SpawnActorDeferred 를 통해 액터를 생성 후 초기화할 때 사용할 함수
	FORCEINLINE void Initialize(EItemEffect EffectType, EItemRareLevel RareLevel) { ItemEffectType = EffectType; ItemRareLevel = RareLevel; }

public:
protected:
	// 아이템의 희귀도 enum 변수
	UPROPERTY(EditAnywhere)
		EItemRareLevel ItemRareLevel;
	// 아이템의 효과 enum 변수
	UPROPERTY(EditAnywhere)
		EItemEffect ItemEffectType;

	// 오버랩 범위 SphereComponent
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USphereComponent> SphereComponent;
	// 상호작용 게이지 Widget Component
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UWidgetComponent> GaugeWidgetComponent;
	// Text Render
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UTextRenderComponent> TextRenderComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UStaticMeshComponent> BodyStaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UStaticMeshComponent> ItemObjectMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TObjectPtr<UStaticMesh>> ItemObjectStaticMeshes;

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

	UPROPERTY()
		TObjectPtr<UProgressBar> InteractionBar;

	float RemoveTime;
private:


};
