#include "TSpectator.h"
#include "Engine.h"

ATSpectator::ATSpectator()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName("BlockAll");
	RootComponent = Collision;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->UpdatedComponent = RootComponent;
}

void ATSpectator::BeginPlay()
{
	Super::BeginPlay();
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
}

void ATSpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
