#include "Player/Weapon/Projectile.h"
#include "Player/PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"

#include "Flag/FlagActor.h"
#include "Game/ShooterMultiGameMode.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
    APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
    if (Character != nullptr)
    {
        UPrimitiveComponent* OtherPrimitiveComponent = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());

        if (OtherPrimitiveComponent && OtherPrimitiveComponent->IsOverlappingComponent(Character->headBoxCollision))
        {
            Character->PlayOnhitAnimMontage();
            Character->OnHitWithDamage(damage * 3);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HeadShot"));
        }
        else
        {
            Character->PlayOnhitAnimMontage();
            Character->OnHitWithDamage(damage);
        }

        SetActorHiddenInGame(true);
        OnProjectileHit();

        return; //used to stop the function from running if it hits the player
    }

    AFlagActor* FlagActor = Cast<AFlagActor>(OtherActor);
    if(FlagActor != nullptr)
    {
        FlagActor->OnHit(m_team);
        return; //used to stop the function from running if it hits the flag
    }

}

void AProjectile::SetProjectileTeam(ETeam _team)
{
    m_team = _team;
}