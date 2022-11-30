#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
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

	//애니메이션 세팅
	//AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer'
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>( &animInstance, "AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer_C'" );
	GetMesh()->SetAnimInstanceClass( animInstance );


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

	PlayerInputComponent->BindAxis( "MoveForward", this, &ACPlayer::OnMoveForward );
	PlayerInputComponent->BindAxis( "MoveRight", this, &ACPlayer::OnMoveRight );
	PlayerInputComponent->BindAxis( "HorizontalLook", this, &ACPlayer::OnHorizontalLook );
	PlayerInputComponent->BindAxis( "VerticalLook", this, &ACPlayer::OnVerticalLook );
	PlayerInputComponent->BindAction( "Running", EInputEvent::IE_Pressed, this, &ACPlayer::OnRunning );
	PlayerInputComponent->BindAction( "Running", EInputEvent::IE_Released, this, &ACPlayer::OffRuning );
}

void ACPlayer::OnMoveForward( float axis )
{
	FRotator rotator = FRotator( 0.0f, GetControlRotation().Yaw, 0.0f );
	FVector direction = FQuat( rotator ).GetForwardVector().GetSafeNormal2D();
	AddMovementInput( direction, axis );
}

void ACPlayer::OnMoveRight( float axis )
{
	FRotator rotator = FRotator( 0.0f, GetControlRotation().Yaw, 0.0f );
	FVector direction = FQuat( rotator ).GetRightVector().GetSafeNormal2D();
	AddMovementInput( direction, axis );
}

void ACPlayer::OnHorizontalLook( float axis )
{
	AddControllerYawInput( axis );
}

void ACPlayer::OnVerticalLook( float axis )
{
	AddControllerPitchInput( bInverseVerticalCamera ? -axis : axis );
}

void ACPlayer::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ACPlayer::OffRuning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}
