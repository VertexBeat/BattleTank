// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


public:
	// called by the engine, when actor damage is dealt
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController* EventInstigator,AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category ="Health")
	float GetHealthPercent() const;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100.f;

	int32 CurrentHealth = StartingHealth;
};
