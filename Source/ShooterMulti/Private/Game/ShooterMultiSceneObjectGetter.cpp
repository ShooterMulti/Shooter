#include "Game/ShooterMultiSceneObjectGetter.h"

AShooterMultiSceneObjectGetter* AShooterMultiSceneObjectGetter::m_instance = nullptr;

void AShooterMultiSceneObjectGetter::BeginPlay()
{
	Super::BeginPlay();
	if(!m_instance)
		m_instance = this;
}

AShooterMultiSceneObjectGetter::AShooterMultiSceneObjectGetter()
{
	PrimaryActorTick.bCanEverTick = false;
}

AShooterMultiSceneObjectGetter* AShooterMultiSceneObjectGetter::GetInstance()
{
	return m_instance;
}
