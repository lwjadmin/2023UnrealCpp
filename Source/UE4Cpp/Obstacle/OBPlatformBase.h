// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OBPlatformBase.generated.h"

UCLASS()
class UE4CPP_API AOBPlatformBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOBPlatformBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = Component)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CustomMaterial)
    FLinearColor MeshBaseColor1 = FLinearColor(0, 0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CustomMaterial)
	FLinearColor MeshBaseColor2 = FLinearColor(1, 1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CustomMaterial)
	float MeshRoughness = 0.75;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CustomMaterial)
	float MeshMetalic = 0.25;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CustomMaterial)
	bool bSetRandomizedColor = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CustomMaterial)
	bool bSetRandomizedRoughness = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CustomMaterial)
	bool bSetRandomizedMetalic = false;
};
