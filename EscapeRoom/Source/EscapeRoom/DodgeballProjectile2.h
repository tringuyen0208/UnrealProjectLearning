// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DodgeballProjectile2.generated.h"

UCLASS()
class ESCAPEROOM_API ADodgeballProjectile2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile2();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The sound the dodgeball will make when it bounces off of a surface
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* BounceSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundAttenuation* BoundSoundAttenuation;

	UPROPERTY(EditAnywhere, Category = Particles)
		class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* DamageSound;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

};
