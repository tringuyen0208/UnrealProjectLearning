// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ESCAPEROOM_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Change the rotation of the character to face the given actor
	void LookAtActor(AActor* TargetActor);

	//Can the enemy see the given character
	bool CanSeeActor(const AActor* const TargetActor) const;

	void ThrowDodgeball();
	FTimerHandle ThrowTimerHandle;
	float ThrowingInterval = 2.f;
	float ThrowingDelay = 0.5f;

	//The class used to spawn a dodgeball object
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball)
		TSubclassOf<AActor> DodgeballClass;
};
