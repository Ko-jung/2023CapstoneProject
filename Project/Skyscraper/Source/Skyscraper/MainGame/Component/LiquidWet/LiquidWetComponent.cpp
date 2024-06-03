// Fill out your copyright notice in the Description page of Project Settings.


#include "LiquidWetComponent.h"
#include "ClothConfigBase.h"
#include "ClothingAsset.h"
#include "GameFramework/Character.h"
#include "ChaosCloth/ChaosClothConfig.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Skyscraper/MainGame/Actor/Character/SkyscraperCharacter.h"
#include "Engine/Canvas.h"

// Sets default values for this component's properties
ULiquidWetComponent::ULiquidWetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHitCount = 250;
	HitDataOffset = 4;
	// ...
}

void ULiquidWetComponent::AddHitData(FVector2D HitUV, float LiquidDuration)
{
	FLiquidHitData.Add(FLiquidData{ HitUV,LiquidDuration });
	RenderLiquidWet();
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

	OwnerCharacter = Cast<ASkyscraperCharacter>(GetOwner());

	InitialSetting();
}

void ULiquidWetComponent::AddSkirtCollisionMesh()
{
	UStaticMeshComponent* SkirtCollisionMesh = Cast<UStaticMeshComponent>(OwnerCharacter->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, FTransform{}, false));

	SkirtCollisionMesh->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules{ EAttachmentRule::SnapToTarget,true }, FName{ "SkirtSocket" });
	SkirtCollisionMesh->SetStaticMesh(OwnerCharacter->GetSkirtStaticMesh());

	SkirtCollisionMesh->SetVisibility(false);
	SkirtCollisionMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
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

void ULiquidWetComponent::SetSkirtMaterialDynamicInstance()
{
	if (!OwnerCharacter) return;

	//UMaterial* SkirtMaterial = OwnerCharacter->GetSkirtMaterial();
	//MaterialDynamicInstanceObj = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SkirtMaterial);
	//OwnerCharacter->GetMesh()->SetMaterial(OwnerCharacter->GetSkirtMaterialValue(), MaterialDynamicInstanceObj);

	MaterialDynamicInstanceObj =  OwnerCharacter->GetMesh()->CreateAndSetMaterialInstanceDynamic(OwnerCharacter->GetSkirtMaterialValue());
}

void ULiquidWetComponent::CreateRenderTargetAndSetMaterialParam()
{
	if (!MaterialDynamicInstanceObj) return;

	// 렌더타겟 생성 (HitData담는 캔버스)
	RT_HitData = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), MaxHitCount * HitDataOffset, 1);
	RT_HitData->AddressX = TextureAddress::TA_Clamp;
	RT_HitData->AddressY = TextureAddress::TA_Clamp;

	// 머테리얼 파라미터로 렌더타겟 연결
	MaterialDynamicInstanceObj->SetTextureParameterValue(FName("Tex"), RT_HitData);
	// 최대 Hit 갯수 연결
	MaterialDynamicInstanceObj->SetScalarParameterValue(FName("XSize"), MaxHitCount);
}

void ULiquidWetComponent::InitialSetting()
{
	AddSkirtCollisionMesh();
	FindOwnerClothConfigBase();
	SetSkirtMaterialDynamicInstance();
	CreateRenderTargetAndSetMaterialParam();
}

void ULiquidWetComponent::SetOwnerCharacterNewMesh()
{
	if (!OwnerCharacter) return;

	USkeletalMesh* CurrentMeshAsset = OwnerCharacter->GetMesh()->GetSkeletalMeshAsset();
	OwnerCharacter->GetMesh()->SetSkeletalMeshAsset(nullptr);
	OwnerCharacter->GetMesh()->SetSkeletalMeshAsset(CurrentMeshAsset);
	//OwnerCharacter->GetMesh()

}

void ULiquidWetComponent::RenderLiquidWet()
{
	if (!(RT_HitData && MaterialDynamicInstanceObj)) return;

	UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), RT_HitData);

	UCanvas* Canvas{};
	FVector2D Size{};
	FDrawToRenderTargetContext Context{};
	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(GetWorld(), RT_HitData,Canvas , Size, Context);


	// 모든 충돌 데이터를 RT_HitData 렌더타겟에 담기
	for(int i =0; i<FLiquidHitData.Num();++i)
	{
		FVector2D ScreenPosition{ static_cast<float>((HitDataOffset * i) - (HitDataOffset / 2)),0};
		
		FVector2D ScreenSize{  static_cast<float>(HitDataOffset),1 };

		FVector2D CoordinatePosition{ 0,0 };
		FVector2D CoordinateSize{ 1,1 };

		//실질적인 데이터가 담기는 변수
		FLinearColor RenderColor{0,0,0,1};
		FLiquidData& Data = FLiquidHitData[i];
		RenderColor.R = Data.HitUV.X;
		RenderColor.G = Data.HitUV.Y;
		RenderColor.B = Data.HitDuration / 50;

		Canvas->K2_DrawTexture(nullptr, ScreenPosition, ScreenSize, CoordinatePosition, CoordinateSize, RenderColor);;
	}

	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(GetWorld(), Context);

	// 머테리얼 내 텍스쳐 설정
	MaterialDynamicInstanceObj->SetScalarParameterValue(FName("HitCounts"), FLiquidHitData.Num());
	MaterialDynamicInstanceObj->SetTextureParameterValue(FName("Tex"), RT_HitData);


}

