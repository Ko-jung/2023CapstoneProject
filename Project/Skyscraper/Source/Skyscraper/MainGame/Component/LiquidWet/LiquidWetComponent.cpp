// Fill out your copyright notice in the Description page of Project Settings.


#include "LiquidWetComponent.h"
#include "ClothConfigBase.h"
#include "ClothingAsset.h"
#include "GameFramework/Character.h"
#include "ChaosCloth/ChaosClothConfig.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values for this component's properties
ULiquidWetComponent::ULiquidWetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULiquidWetComponent::SetSkirtGravity(float value)
{
	if (SkirtConfig)
	{
		// 값 조정
		UE_LOG(LogTemp, Warning, TEXT("기존: %f,"), SkirtConfig->GravityScale);
		SkirtConfig->GravityScale = value;

		// OwnerCharacter의 mesh 다시 로드하여 값 로드
		SetOwnerCharacterNewMesh();
	}
}


// Called when the game starts
void ULiquidWetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	FindOwnerClothConfigBase();
	// ...

}

void ULiquidWetComponent::FindOwnerClothConfigBase()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	USkeletalMeshComponent* Mesh = Character->GetMesh();
	if (!Mesh) return;

	if (!Mesh->GetSkeletalMeshAsset()) return;


	// 캐릭터 메시로부터 Skirt의 ClothingData 구하기
	auto MeshClothingAssetsArray = Mesh->GetSkeletalMeshAsset()->GetMeshClothingAssets();
	for (TObjectPtr<UClothingAssetBase> Object : MeshClothingAssetsArray)
	{
		if (!UKismetStringLibrary::Contains(Object->GetName(), FString{ "Skirt" })) continue;

		UClothingAssetCommon* Common = Cast<UClothingAssetCommon>(Object);
		if (Common)
		{
			// ClothingData내의 ChaosClothConfig 구하기
			if (Common->ClothConfigs.Contains("ChaosClothConfig"))
			{
				SkirtConfig = Cast<UChaosClothConfig>(*Common->ClothConfigs.Find("ChaosClothConfig"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("못찾았다!"));
			}
		}

	}


}

void ULiquidWetComponent::SetOwnerCharacterNewMesh()
{
	if (!OwnerCharacter) return;

	USkeletalMesh* CurrentMeshAsset = OwnerCharacter->GetMesh()->GetSkeletalMeshAsset();
	OwnerCharacter->GetMesh()->SetSkeletalMeshAsset(nullptr);
	OwnerCharacter->GetMesh()->SetSkeletalMeshAsset(CurrentMeshAsset);
	//OwnerCharacter->GetMesh()

}


// Called every frame
void ULiquidWetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

