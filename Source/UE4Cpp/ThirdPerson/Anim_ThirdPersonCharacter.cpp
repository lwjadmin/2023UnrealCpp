// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ThirdPersonCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


UAnim_ThirdPersonCharacter::UAnim_ThirdPersonCharacter()
{
    
}

void UAnim_ThirdPersonCharacter::NativeBeginPlay()
{

}

void UAnim_ThirdPersonCharacter::NativeUpdateAnimation(float DeltaSeconds)
{
    auto PawnRef = TryGetPawnOwner();
    if (IsValid(PawnRef))
    {
        MoveSpeed = PawnRef->GetVelocity().Size();

        ACharacter* Char = Cast<ACharacter>(PawnRef);
        if (Char)
        {
            bIsInAir = Char->GetMovementComponent()->IsFalling();
        }
    }
}
