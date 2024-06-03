// Fill out your copyright notice in the Description page of Project Settings.


#include "TestDefaultPawnForLiquid.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainGame/Actor/Character/SkyscraperCharacter.h"
#include "MainGame/Component/LiquidWet/LiquidWetComponent.h"

void ATestDefaultPawnForLiquid::Fire() {
	FVector Start = GetActorLocation();
	FVector End = Start + UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * 1000;

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UCollisionProfile::Get()->ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

	EDrawDebugTrace::Type DrawDebugType{EDrawDebugTrace::ForDuration};

	FHitResult OutHit{};
	bool HitResult = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, true, IgnoreActors, DrawDebugType, OutHit, true, FLinearColor::Red, FLinearColor::Blue, 5.0f);


	if(HitResult)
	{
		if(ASkyscraperCharacter* Character = Cast<ASkyscraperCharacter>(OutHit.GetActor()))
		{
			FVector2D HitUV{};
			UGameplayStatics::FindCollisionUV(OutHit,0,HitUV);
			UE_LOG(LogTemp, Warning, TEXT("UV 결과 - %f %f"), HitUV.X, HitUV.Y);
			Character->LiquidWetComponent->AddHitData(HitUV, UKismetMathLibrary::RandomFloatInRange(8.0, 12.0));
		}
	}
}

void ATestDefaultPawnForLiquid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Cast<APlayerController>(GetController())->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		Fire();
	}
}
