// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actor/ControllableWeapon.h"

#include "Gameplay/FWeGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Gameplay/Components/MagicBallMovementComponent.h"
#include "Gameplay/Input/WeInputComponent.h"


// Sets default values
AControllableWeapon::AControllableWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&AControllableWeapon::OnControllableWeaponBeginOverlap);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

	InputComponent = CreateDefaultSubobject<UWeInputComponent>("inputComponent");
	MovementComp = CreateDefaultSubobject<UMagicBallMovementComponent>(TEXT("WeaponMovement"));
}

// Called when the game starts or when spawned
// Used to set the player's view target to the controllable weapon
void AControllableWeapon::BeginPlay()
{
	Super::BeginPlay();

	bHasExploded = false;
	check(PlayerController);
	EnableInput(PlayerController);
	PlayerController->PlayerCameraManager->SetViewTarget(this);
	
}

void AControllableWeapon::SetupInput()
{

	const FWeGameplayTags& GameplayTags = FWeGameplayTags::Get();

	Cast<UWeInputComponent>(InputComponent)->BindActionByTag(InputConfig,GameplayTags.InputTag_Look_Mouse,ETriggerEvent::Triggered,this,&AControllableWeapon::Input_Steer);
	Cast<UWeInputComponent>(InputComponent)->BindActionByTag(InputConfig,GameplayTags.InputTag_Fire,ETriggerEvent::Triggered,this,&AControllableWeapon::Input_Detonate);
	

	
	
}

// Called every frame
void AControllableWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AControllableWeapon::Input_Steer(const FInputActionValue& InputActionValue)
{
	const FVector2D SteerValue = InputActionValue.Get<FVector2D>();

	UE_LOG(LogTemp,Error,TEXT("Steer"));
	if(SteerValue.X != 0.0f)
	{
		MovementComp->AddYawInput(SteerValue.X);
		
	}
	if(SteerValue.Y != 0.0)
	{
		MovementComp->AddPitchInput(SteerValue.Y);
	}
}

void AControllableWeapon::Explode(AActor* HitActor, const FHitResult& HitResult)
{
	if(!bHasExploded)
	{
		bHasExploded = true;
		OnExplodedDelegate.Broadcast(this,HitActor,HitResult);
		SetHidden(true);
		Destroy();
	}
}

void AControllableWeapon::Input_Detonate(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp,Error,TEXT("Attack"));
	if(!bHasExploded)
	{
		Explode(nullptr,FHitResult());
		
	}
}

void AControllableWeapon::BecomeViewTarget(APlayerController* PC)
{
	Super::BecomeViewTarget(PC);
	SetupInput();
}

void AControllableWeapon::EndViewTarget(APlayerController* PC)
{
	Super::EndViewTarget(PC);
	DisableInput(PC);
}

void AControllableWeapon::OnControllableWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	Explode(OtherActor,SweepResult);
	
	
}

