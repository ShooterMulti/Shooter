#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
enum ETeam;

UCLASS()
class SHOOTERMULTI_API AProjectile : public AActor
{
	GENERATED_BODY()
private:
	ETeam m_team;

public:	
	AProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	int32 damage = 1;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnProjectileHit();

	void SetProjectileTeam(ETeam _team);
};
