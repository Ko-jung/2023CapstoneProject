// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skyscraper/Enum/ECharacterSelect.h"
#include "Subsystems/EngineSubsystem.h"
#include "SkyscraperEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API USkyscraperEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	USoundBase* GetSkyscraperSound(FName RowName) const;

	UFUNCTION(BlueprintCallable)
		UTexture2D* GetSkyscraperCharacterTexture(ECharacterSelect CharacterType);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FName GetCharacterNameByECharacterSelect(ECharacterSelect CharacterSelect);
private:

public:

protected:
	UPROPERTY()
		TObjectPtr<UDataTable> SoundDataTable;

	UPROPERTY()
		TObjectPtr<UDataTable> TextureDataTable;

private:
};

