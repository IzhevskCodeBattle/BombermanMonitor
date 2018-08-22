#include "TDirector.h"

ATDirector::ATDirector()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Turret = CreateDefaultSubobject<USceneComponent>(TEXT("Turret"));
	Turret->SetupAttachment(RootComponent);
}

void ATDirector::BeginPlay()
{
	Super::BeginPlay();
}
