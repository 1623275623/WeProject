// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "ShaderPrintParameters.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "WeProject/WeProject.h"


// Sets default values
AGameProjectile::AGameProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	
	

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->InitialSpeed = 800.0f;
	ProjectileMovementComponent->MaxSpeed = 900.0;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	
	
}

bool AGameProjectile::IsValidOverlap(AActor* OtherActor)
{
	if(Params.SourceAbilitySystemComponent == nullptr)
		return false;

	AActor* SourceAvatarActor = Params.SourceAbilitySystemComponent->GetAvatarActor();
	if(SourceAvatarActor == OtherActor) return false;

	
	return true;
	
	
}

// Called when the game starts or when spawned
void AGameProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AGameProjectile::OnSphereOverlap);
}

void AGameProjectile::OnHit()
{
	
}

void AGameProjectile::Destoryed()
{
	
	Super::Destroy();
}

void AGameProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(!IsValidOverlap(OtherActor)) return;
	if(!bHit) OnHit();
	
	if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		//const FVector DeathImpulse = GetActorForwardVector() *
			TargetASC->ApplyGameplayEffectToSelf(EffectClass->GetDefaultObject<UGameplayEffect>(),1.0,TargetASC->MakeEffectContext());
		
	}

		
	Destoryed();
	
	
}

// Called every frame
void AGameProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

