#pragma once

#include "CoreMinimal.h"
#include "SkyscraperCharacter.h"
#include "BoomerangCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SKYSCRAPER_API ABoomerangCharacter : public ASkyscraperCharacter
{
	GENERATED_BODY()
public:
	ABoomerangCharacter();

protected:
private:

public:
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost")
	TObjectPtr<UStaticMeshComponent> Boomerang_R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost")
		TObjectPtr<UStaticMeshComponent> Boomerang_L;

private:
};

