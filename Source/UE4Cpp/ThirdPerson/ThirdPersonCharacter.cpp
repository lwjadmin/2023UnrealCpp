// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_DefaultMesh_Male(TEXT("SkeletalMesh'/Game/BPThirdPerson/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SK_DefaultMesh_Male.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_DefaultMesh_Male.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	}


	ConstructorHelpers::FClassFinder<UAnimInstance> ACP_TPCharacter(TEXT("AnimBlueprint'/Game/BPThirdPerson/CppBlueprint/ACP_TPCharacter.ACP_TPCharacter_C'"));
	if (ACP_TPCharacter.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ACP_TPCharacter.Class);
	}

	//캐릭터를 사용자의 마우스 회전입력에 따라 회전
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 10.0f);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	//카메라는 폰을 사용자의 마우스 회전입력에 따라 회전시키지 않도록 적용
	Camera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("LookUp", this, &AThirdPersonCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AThirdPersonCharacter::Turn);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacter::MoveForward);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AThirdPersonCharacter::JumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AThirdPersonCharacter::JumpReleased);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AThirdPersonCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &AThirdPersonCharacter::ZoomOut);
}

void AThirdPersonCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AThirdPersonCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AThirdPersonCharacter::MoveRight(float AxisValue)
{
	FRotator rotation = Controller->GetControlRotation();
	//MakeRotator(Yaw Only)
	FRotator yawrotation(0, rotation.Yaw, 0);
	//GetRightVector
	FVector Direction = FRotationMatrix(yawrotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void AThirdPersonCharacter::MoveForward(float AxisValue)
{
	FRotator rotation = Controller->GetControlRotation();
	//MakeRotator(Yaw Only)
	FRotator yawrotation(0, rotation.Yaw, 0);
	//GetRightVector
	FVector Direction = FRotationMatrix(yawrotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);

}

void AThirdPersonCharacter::JumpPressed()
{
	Jump();
}

void AThirdPersonCharacter::JumpReleased()
{
	StopJumping();
}

void AThirdPersonCharacter::ZoomIn()
{
	SpringArm->TargetArmLength = UKismetMathLibrary::FClamp(SpringArm->TargetArmLength * 0.95, 200, 600);
}

void AThirdPersonCharacter::ZoomOut()
{
	SpringArm->TargetArmLength = UKismetMathLibrary::FClamp(SpringArm->TargetArmLength * 1.05, 200, 600);
}
