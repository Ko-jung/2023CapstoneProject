// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSpawner.h"

#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ADamageSpawner::ADamageSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Damage = 100;	// Initialize()
	DigitScale = 0.5f; // Initialize()
	DamageLocationOffset = FVector(0.0f, 0.0f, 0.0f);
	TextOffsetY = 0.0f;

	SpawnerRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SpawnerRootComponent);

	{ // 숫자 텍스쳐 로드
		const ConstructorHelpers::FObjectFinder<UTexture> Digit0Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/0.0'"));
		DigitTexture.Add(Digit0Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit1Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/1.1'"));
		DigitTexture.Add(Digit1Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit2Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/2.2'"));
		DigitTexture.Add(Digit2Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit3Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/3.3'"));
		DigitTexture.Add(Digit3Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit4Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/4.4'"));
		DigitTexture.Add(Digit4Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit5Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/5.5'"));
		DigitTexture.Add(Digit5Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit6Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/6.6'"));
		DigitTexture.Add(Digit6Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit7Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/7.7'"));
		DigitTexture.Add(Digit7Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit8Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/8.8'"));
		DigitTexture.Add(Digit8Ref.Object);
		const ConstructorHelpers::FObjectFinder<UTexture> Digit9Ref(TEXT("/Script/Engine.Texture2D'/Game/2019180031/MainGame/Fbx/Damage/9.9'"));
		DigitTexture.Add(Digit9Ref.Object);
	}

	{ // 나이아가라 시스템 로드
		const ConstructorHelpers::FObjectFinder<UNiagaraSystem> FX_FloatingDamageRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/2019180031/MainGame/Fbx/Damage/FX_FloatingDamage.FX_FloatingDamage'"));
		FX_FloatingDamage = FX_FloatingDamageRef.Object;
	}
	

}



// Called when the game starts or when spawned
void ADamageSpawner::BeginPlay()
{
	Super::BeginPlay();

	{ // 대미지 랜덤 생성 위치 설정
		DamageLocationOffset = UKismetMathLibrary::RandomUnitVector() * 50.0f - 25.0f;
	}

	{ // 대미지 자릿수에 따른 텍스트 y 오프셋 설정
		std::string DamageDigit = std::to_string(Damage);
		TextOffsetY = (float)DamageDigit.size() / -2.0f;
		{ // 대미지 이펙트 소환
			SpawnDamageFX(DamageDigit);
		}
	}

	Destroy();
}

void ADamageSpawner::SpawnDamageFX(const std::string& DamageString)
{
	const FVector SpawnLocation = GetActorLocation() + DamageLocationOffset;
	const FRotator SpawnRotator = GetActorRotation();
	const FVector SpawnScale = { DigitScale,DigitScale,DigitScale };
	for (int i = 0; i < DamageString.size(); ++i)
	{
		UNiagaraComponent* FX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), FX_FloatingDamage,
			SpawnLocation, SpawnRotator, SpawnScale);
		Cast<USceneComponent>(FX)->AddLocalOffset(FVector(0.0f, TextOffsetY, 0.0f));
		TextOffsetY = TextOffsetY + (25.0f * DigitScale);
		const int DamageStringDigit = DamageString[i] - '0';	
		UNiagaraFunctionLibrary::SetTextureObject(FX, TEXT("user.Digit"), DigitTexture[DamageStringDigit]);
		
	}
}

// Called every frame
void ADamageSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageSpawner::Initialize(float InDamage, float InScale)
{
	Damage = InDamage;
	DigitScale = InScale;
}

