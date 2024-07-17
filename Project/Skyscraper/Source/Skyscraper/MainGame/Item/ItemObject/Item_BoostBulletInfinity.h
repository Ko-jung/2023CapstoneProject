#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "Skyscraper/Enum/EItemRareLevel.h"
#include "Item_BoostBulletInfinity.generated.h"

/**
 *
 */
UCLASS()
class SKYSCRAPER_API UItem_BoostBulletInfinity : public UItemObject
{
	GENERATED_BODY()
public:
	UItem_BoostBulletInfinity();
	virtual void SetItemRare(EItemRareLevel RareLevel) override;
	virtual ~UItem_BoostBulletInfinity() override;

	virtual void DoItemEffect(ASkyscraperCharacter* UsedCharacter) override;
};


