#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	/*
	SpringArm = CreateDefaultSubobject<USpringArmComponent>( "SpringArm" );
	SpringArm->SetupAttachment( GetCapsuleComponent() );

	Camera = CreateDefaultSubobject<UCameraComponent>( "Camera" );
	Camera->SetupAttachment( SpringArm );
	*/

	CHelpers::CreateComponent<USpringArmComponent>( this, &SpringArm, "SpringArm", GetCapsuleComponent() );
	CHelpers::CreateComponent<UCameraComponent>( this, &Camera, "Camera", SpringArm );

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>( &mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'" );
	GetMesh()->SetSkeletalMesh( mesh );

	//캐릭터 위치 세팅
	GetMesh()->SetRelativeLocation( FVector( 0, 0, -90 ) );
	GetMesh()->SetRelativeRotation( FRotator(0,-90,0)  );

	//Spring Arm 위치 조정
	SpringArm->SetRelativeLocation( FVector( 0, 0, 60 ) );
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false; //스프링 암 중간에 충돌 테스트 끄기
	SpringArm->bUsePawnControlRotation = true;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

