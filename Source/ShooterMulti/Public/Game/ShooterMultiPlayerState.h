#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShooterMultiPlayerState.generated.h"


enum ETeam;

UCLASS()
class SHOOTERMULTI_API AShooterMultiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	FString username;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int life;
	UPROPERTY(Replicated, BlueprintReadWrite)
	TEnumAsByte<ETeam> team /*= ETeam::None*/;

public:
	AShooterMultiPlayerState() = default;

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void CopyProperties(APlayerState* PlayerState) override;
};
