// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Fetch the character currently being controlled by the player
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	//look at the player character
	LookAtActor(PlayerCharacter);
}

void AEnemyCharacter::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr) return;

	if (CanSeeActor(TargetActor))
	{
		//setting the location of enemy and the target
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();

		//Calculate rotation for start point to face end point
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		//Set enemy rotation to that rotation
		SetActorRotation(LookAtRotation);
	}
}

bool AEnemyCharacter::CanSeeActor(const AActor* const TargetActor) const
{
	if(TargetActor == nullptr)
	return false;

	//store the results of the Line Trace
	FHitResult Hit;
	
	//where the line trace starts and ends
	FVector Start = GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	//The trace channel we want to compare against
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;

	FCollisionQueryParams QueryParams;
	//ignore the actor executing files
	QueryParams.AddIgnoredActor(this);
	//Ignore the target
	QueryParams.AddIgnoredActor(TargetActor);

	//Line trace
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End,Channel,QueryParams);

	//set color green if blocked or red if not blocked
	FColor LineColor = (Hit.bBlockingHit) ? FColor::Green : FColor::Red;

	//Show the line trace inside the game
	DrawDebugLine(GetWorld(), Start, End, LineColor);

	return !Hit.bBlockingHit;


}

// Called to bind functionality to input 

