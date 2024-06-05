// Fill out your copyright notice in the Description page of Project Settings.


#include "interpolator.h"
#include "Math/UnrealMathVectorCommon.h"

// Sets default values
Ainterpolator::Ainterpolator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.bRunOnAnyThread = true;

	auto DefaultRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

}

// Called when the game starts or when spawned
void Ainterpolator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Ainterpolator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (tail.Num() == 0 || !IsValid(tail[0]))
		return;

	AActor* last = this;

	for (size_t i = 0; i < tail.Num(); i++)
	{
		if (IsValid(tail[i]))
		{
			tail[i]->SetActorLocation(
				last->GetActorLocation() + (tail[i]->GetActorLocation() - last->GetActorLocation()) * FMath::Exp2(-DeltaTime / .5f)
			);
			last = tail[i];
		}
	}
	DrawDebugSphere(GetWorld(), GetActorLocation(), 20, 10, FColor::Green);

}

