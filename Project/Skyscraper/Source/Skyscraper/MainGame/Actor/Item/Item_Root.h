// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Skyscraper/MainGame/Interface/Item/ItemInteraction.h"
#include "Item_Root.generated.h"

class ASkyscraperCharacter;
class UProgressBar;
class UTextRenderComponent;
class UWidgetComponent;
class USphereComponent;

UCLASS()
class SKYSCRAPER_API AItem_Root : public AActor, public IItemInteraction
{
	GENERATED_BODY()

	// ������ ���� SphereComponent
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
	// ��ȣ�ۿ� ������ Widget Component
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> GaugeWidgetComponent;
	// Text Render
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextRenderComponent> TextRenderComponent;

	// ��ȣ�ۿ� �ʿ� �ð�
	UPROPERTY(EditAnywhere)
	float RequiredTime;
	// ���� ��ȣ�ۿ� �ð�
	UPROPERTY()
	float CurrentInteractionTime;
	// ���� ���� ��ȣ�ۿ� �ð�
	UPROPERTY()
	float LastInteractionTime;
	// Player - Widget ��
	UPROPERTY()
	TMap<AActor*, UUserWidget*> PlayerAndWidgetMap;
	// ���� ��ȣ�ۿ� ���� ĳ����
	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractionActor;

	// ��ȣ�ۿ� Ű ����
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WBP_InteractionKey;

	UPROPERTY()
	TObjectPtr<UProgressBar> InteractionBar;
	
public:
	// ������
	AItem_Root();

protected:
	// Begin Play
	virtual void BeginPlay() override;
	// End Play
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// ��ȣ�ۿ� �Ϸ�� ó���� ������ ȿ�� �Լ�
	void DoItemEffect(const ASkyscraperCharacter* ItemUsedCharacter);

	// Begin Overlap - SphereComponent
	UFUNCTION()
	void SphereBeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	// End Overlap - SphereComponent
	UFUNCTION()
		void SphereEndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);

	// End Overlap�� �÷��̾��� ������ �����ϴ� �Լ�
	void RemovePlayerWidget(AActor* EndOverlapCharacter);

	// ���α׷��� ���� �ۼ�Ʈ�� �ٲٴ� �Լ�
	void SetProgressBarPercent() const;
public:	
	// Tick Event
	virtual void Tick(float DeltaTime) override;
	// �������̽� - ��ȣ�ۿ� Ű�� ���� ��ȣ�ۿ� �� ����� �Լ�
	virtual void ItemInteraction(AActor* InteractionActor) override;
};


