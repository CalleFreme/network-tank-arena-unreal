// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"
#include "TankPawn.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASpeedBoost::ASpeedBoost()
{
	bReplicates = true;
	SetReplicatingMovement(false);
	bAlwaysRelevant = true;
	UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Box);
	Box->InitBoxExtent(FVector(50.0));
	Box->SetCollisionProfileName(TEXT("OverlapAll"));
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetGenerateOverlapEvents(true);
	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	Mesh->SetupAttachment(Box);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	Mesh->SetStaticMesh(Sphere.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Engine/Functions/Engine_MaterialFunctions02/ExampleContent/HueShift_Mat"));
	Mesh->SetMaterial(0, Material.Object);
}

// Called when the game starts or when spawned
void ASpeedBoost::BeginPlay()
{
	Super::BeginPlay();
}

void ASpeedBoost::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

