// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballProjectile2.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TopDownCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADodgeballProjectile2::ADodgeballProjectile2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);
	SphereComponent->SetCollisionProfileName(FName("Dodgeball"));
	SphereComponent->SetSimulatePhysics(true);
	//Simulation generates Hit events
	SphereComponent->SetNotifyRigidBodyCollision(true);
	// Listen to the OnComponentHit event by binding it to our function
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeballProjectile2::OnHit);

	// Set this Sphere Component as the root component,
	// otherwise collision won't behave properly
	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 2200.f;

}

// Called when the game starts or when spawned
void ADodgeballProjectile2::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(5.f);
}

// Called every frame
void ADodgeballProjectile2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADodgeballProjectile2::OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Reach dodgeball projectile line 56. On hit"));
	if (BounceSound != nullptr && NormalImpulse.Size() > 1000.0f)
	{
		UGameplayStatics::PlaySoundAtLocation(this,
			BounceSound,
			GetActorLocation(),
			1.0f,
			FMath::RandRange(0.7f, 1.3f),
			0.0f,
			BoundSoundAttenuation);
	}

	ATopDownCharacter* Player = Cast<ATopDownCharacter>(OtherActor);
	if (Player != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Reach dodgeball projectile line 70. Cast succeeded"));
		//UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
		//if (HealthComponent != nullptr)
		//{
			//HealthComponent->LoseHealth(Damage);
		//}
		if (DamageSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, DamageSound);
		}
		if (HitParticles != nullptr)
		{
			
			FString ActorNameOfObject = Player->GetActorNameOrLabel();

			FString PositionOfObject = Player->GetActorLocation().ToString();
			UE_LOG(LogTemp, Warning, TEXT("Position for %s is at location %s"), *ActorNameOfObject, *PositionOfObject);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorTransform());
		}
		Destroy();
	}
}

