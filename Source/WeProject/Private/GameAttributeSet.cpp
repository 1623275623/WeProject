// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Gameplay/FWeGameplayTags.h"
#include "Gameplay/GameCharacter.h"
#include "Gameplay/GamePlayerController.h"
#include "Gameplay/WeAbilitySystemFunctionLibrary.h"
#include "Interfaces/CombatInterface.h"
#include "WeProject/WeProjectCharacter.h"




UGameAttributeSet::UGameAttributeSet():Health(100.0),
                                       MaxHealth(100.0),
                                       Mana(100.0),
                                       MaxMana(100.0),
                                       Exp(10.),
                                       Attack(20.0),
                                       CriticalChance(0.1),
                                       Speed(500.0)
{
	
}

void UGameAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.,GetMaxHealth());
		
	}
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxMana());
	}
	
}

void UGameAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Get the Target Actor

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	AGameCharacter* TargetCharacter = nullptr;

	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<AGameCharacter>(TargetActor);
	}

	if(Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		AGameCharacter* SourceCharacter = nullptr;

		if(Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();

			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if(APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}

			if(SourceController )
			{
				SourceCharacter = Cast<AGameCharacter>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<AGameCharacter>(SourceActor);
			}

			if(Context.GetEffectCauser())
			{
				SourceActor = Context.GetEffectCauser();
			}
		}
		FHitResult HitResult;
		if(Context.GetHitResult())
		{
			HitResult = *Context.GetHitResult();
		}

		const float LocalDamageDone = GetDamage();
		UE_LOG(LogTemp,Error,TEXT("%f"),GetDamage());
		SetDamage(0.f);

		if(LocalDamageDone > 0)
		{
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone,0.0f,GetMaxHealth()));
			TargetCharacter->PlayAnimMontage(TargetCharacter->HitReactMontage);
			if(GetHealth() == 0.0f)
			{
				TargetCharacter->bDead = true;
				FTimerHandle Handle;
				GetWorld()->GetTimerManager().SetTimer(Handle,FTimerDelegate::CreateLambda([&]()
				{
					TargetCharacter->Destroy();
				}),3.0,false);
			}
			if(TargetCharacter)
			{
				TargetCharacter->HandleDamage(LocalDamageDone,HitResult,SourceTags,SourceCharacter,SourceActor);

				TargetCharacter->HandleHealthChanged(-LocalDamageDone,SourceTags);
			}
				
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		
	}
	else if(Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		TargetCharacter->HandleMovementSpeedChanged(Data.EvaluatedData.Magnitude,*Data.EffectSpec.CapturedSourceTags.GetAggregatedTags());
	}
	else if(Data.EvaluatedData.Attribute == GetExpAttribute())
	{
		
	}

	
}

void UGameAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UGameAttributeSet::ShowFloatingText(const FEffectProperties& Props, float InDamage, bool bBlockHit,
	bool bCriticalHit) const
{
	if(!IsValid(Props.SourceCharacter) || !IsValid(Props.TargetCharacter)) return;
	if(Props.SourceCharacter != Props.TargetCharacter)
	{
		if(AGamePlayerController* PC = Cast<AGamePlayerController>(Props.SourceCharacter))
		{
			PC->ShowDamageNumber(InDamage,Props.TargetCharacter,bBlockHit,bCriticalHit);
			return;
		}
		if(AGamePlayerController* PC = Cast<AGamePlayerController>(Props.TargetController))
		{
			PC->ShowDamageNumber(InDamage,Props.TargetCharacter,bBlockHit,bCriticalHit);
		}
	}
}

void UGameAttributeSet::HandleInComingDamage(const FEffectProperties& Props)
{
	const float LocalIncomingDamage = GetDamage();

	
	SetDamage(0.0f);
	if(LocalIncomingDamage > 0.f)
	{
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth,0.0f,GetMaxHealth()));
		if(bool bDie = NewHealth < 0.)
		{
			ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetCharacter);
			if(CombatInterface)
			{
				
			}
		}
		else
		{
			if(Props.TargetCharacter->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsBeingShocked(Props.TargetCharacter))
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FWeGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}

			const FVector& KnockbackForce = FVector(20,0,0);
			if(!KnockbackForce.IsNearlyZero(1.0))
			{
				Props.TargetCharacter->LaunchCharacter(KnockbackForce,true,true);
			}
		}

		const bool bBlock = UWeAbilitySystemFunctionLibrary::IsBlockHit(Props.EffectContextHandle);
		const bool bCriticalHit = UWeAbilitySystemFunctionLibrary::IsCriticalHit(Props.EffectContextHandle);
		ShowFloatingText(Props,LocalIncomingDamage,bBlock,bCriticalHit);
	
	}
	
}

void UGameAttributeSet::HandleInComingExp(const FEffectProperties& Props)
{
	const float LocalIncomingXP = GetExp();
	SetExp(0.0f);

	
	
}

void UGameAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if(IsValid(Props.SourceASC) &&Props.SourceASC->AbilityActorInfo &&Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if(Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if(const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if(Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
		
	}
	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
		
	}
}
