// Fill out your copyright notice in the Description page of Project Settings.


#include "Reactor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AReactor::AReactor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.bRunOnAnyThread = true;

	auto DefaultRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
}

// Called when the game starts or when spawned
void AReactor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AReactor::Tick(float DeltaTime)
{
	if (anchor == nullptr)
		return;

	Super::Tick(DeltaTime);
	FString text = "";
	auto myPosition     =   this->GetActorLocation();
	auto anchorPosition = anchor->GetActorLocation();

	if (myPosition.Z > anchorPosition.Z)
	{
		text += "above";
	}
	else if (myPosition.Z < anchorPosition.Z)
	{
		text += "below";
	}

	auto anchorForward = anchor->GetActorForwardVector();
	DrawDebugLine(GetWorld(), anchorPosition, anchorPosition + anchorForward*1000,FColor::Blue);


	auto posDiff = (myPosition-anchorPosition).GetSafeNormal();

	auto dot = anchorForward.Dot(posDiff);

	if (dot > 0)
	{
		text += " in fornt";
	}
	else if (dot < 0)
	{
		text += " behind";
	}

	DrawDebugSphere(GetWorld(), myPosition, 20, 10, FColor::Red);
	DrawDebugString(GetWorld(), myPosition, text, this, FColor::White, 0);
}

