// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);
	SphereCollision->InitSphereRadius(50.0f);
	/*-------------------------------------------------------------------------------------
	A. Collision -> Simulation Generates Hit Events
	EX1) SphereCollision->SetNotifyRigidBodyCollision(true);

	B. Collision -> Generate Overlap Events 
	EX1) SphereCollision->SetGenerateOverlapEvents(false);

	C. Collision -> Can Character Step Up On
	   ECB_No     = ĳ���Ͱ� �� ������Ʈ�� �ö�Ż �� ����.
	   ECB_Yes    = ĳ���Ͱ� �� ������Ʈ�� �ö�Ż �� �ִ�.
	   ECB_Owner  = ���Ͱ� �����ϵ�, �⺻���� True�̴�.
	EX1) SphereCollision->CanCharacterStepUpOn = ECB_No;
	
	D. Collision -> Collision Presets
	EX1) SphereCollision->SetCollisionProfileName("BlockAllDynamic");

	E. Collision -> Collision Presets : Collision Enabled 
	   ECollisionEnabled::NoCollision     = �浹ó���� �߻����� �ʴ´�. 
	   ECollisionEnabled::QueryOnly       = �������� �������� ������ �Լ��� ź��.
	   ECollisionEnabled::PhysicsOnly     = �������� �����ϵ� �Լ��� ��ź��.
	   ECollisionEnabled::QueryAndPhysics = �������� �����ϰ� �Լ��� ź��.
	EX1) SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	F. Collision -> Collision Presets : Object Type 
	EX1) SphereCollision->SetCollisionObjectType(ECC_WorldStatic);

	G. Collision -> Collision Presets : Collision Responses
	EX1) SphereCollision->SetCollisionResponseToAllChannels(ECR_Block);
	EX2) SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	-------------------------------------------------------------------------------------*/

	SphereCollision->SetCollisionProfileName("OverlapAllDynamic");
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnComponentBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ACoin::OnComponentEndOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereCollision);
	StaticMesh->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StaticMesh->AddLocalRotation(FRotator(0.0f, MoveSpeed * DeltaTime, 0.0f));
}

void ACoin::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, TEXT("Hit!"));
}

void ACoin::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, TEXT("BeginOverlap!"));
}

void ACoin::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, TEXT("EndOverlap!"));
}

