// Fill out your copyright notice in the Description page of Project Settings.


#include "OBPlatformBase.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AOBPlatformBase::AOBPlatformBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_EngineCubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (SM_EngineCubeMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(SM_EngineCubeMesh.Object);
	}
	ConstructorHelpers::FObjectFinder<UMaterial> M_GridPlane(TEXT("Material'/Game/BPBallRunner/Material/M_GridPlane.M_GridPlane'"));
	if (M_GridPlane.Succeeded())
	{
		StaticMesh->SetMaterial(0, M_GridPlane.Object);
	}
}

// Called when the game starts or when spawned
void AOBPlatformBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOBPlatformBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOBPlatformBase::OnConstruction(const FTransform& Transform)
{
	//1. Set M_GridPlane XSize
	float XSize = Transform.GetScale3D().X == 1 ? 1 : (Transform.GetScale3D().X / 2);
	StaticMesh->SetScalarParameterValueOnMaterials(TEXT("XSize"), XSize);
	//2. Set M_GridPlane YSize
	float YSize = Transform.GetScale3D().Y == 1 ? 1 : (Transform.GetScale3D().Y / 2);
	StaticMesh->SetScalarParameterValueOnMaterials(TEXT("YSize"), YSize);
	//3. Set M_GridPlane GridColor1
	float RandomGridColorHue1 = UKismetMathLibrary::RandomFloatInRange(0.0f, 179.9f);
	FLinearColor RandomGridColor1 = UKismetMathLibrary::HSVToRGB(
		RandomGridColorHue1, 1.0f, 1.0f, 1.0f);
	MeshBaseColor1 = bSetRandomizedColor ? RandomGridColor1 : MeshBaseColor1;
	FVector GridColor1 = UKismetMathLibrary::Conv_LinearColorToVector(MeshBaseColor1);
	StaticMesh->SetVectorParameterValueOnMaterials(TEXT("GridColor1"), GridColor1);
	//4. Set M_GridPlane GridColor2
	float RandomGridColorHue2 = RandomGridColorHue1 + 180.0f;
	FLinearColor RandomMeshBaseColor2 = UKismetMathLibrary::HSVToRGB(
		RandomGridColorHue2, 1.0f, 1.0f, 1.0f);
	MeshBaseColor2 = bSetRandomizedColor ? RandomMeshBaseColor2 : MeshBaseColor2;
	FVector GridColor2 = UKismetMathLibrary::Conv_LinearColorToVector(MeshBaseColor2);
	StaticMesh->SetVectorParameterValueOnMaterials(TEXT("GridColor2"), GridColor2);
	//5. Set M_GridPlane Roughness
	float RandomRoughness = UKismetMathLibrary::RandomFloatInRange(0.2, 0.8);
	MeshRoughness = bSetRandomizedRoughness ? RandomRoughness : MeshRoughness;
	StaticMesh->SetScalarParameterValueOnMaterials(TEXT("Roughness"), MeshRoughness);
	//6. Set M_GridPlane Metalic
	float RandomMetalic = UKismetMathLibrary::RandomFloatInRange(0.2, 0.8);
	MeshMetalic = bSetRandomizedMetalic ? RandomMetalic : MeshMetalic;
	StaticMesh->SetScalarParameterValueOnMaterials(TEXT("Metalic"), MeshMetalic);


}



