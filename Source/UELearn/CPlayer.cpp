#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

// 22.12.16 added for rifle
#include "CRifle.h"

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

	//ĳ���� ��ġ ����
	GetMesh()->SetRelativeLocation( FVector( 0, 0, -90 ) );
	GetMesh()->SetRelativeRotation( FRotator(0,-90,0)  );

	//�ִϸ��̼� ����
	//AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer'
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>( &animInstance, "AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer_C'" );
	GetMesh()->SetAnimInstanceClass( animInstance );


	//Spring Arm ��ġ ����
	SpringArm->SetRelativeLocation( FVector( 0, 0, 60 ) );
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false; //������ �� �߰��� �浹 �׽�Ʈ ����
	SpringArm->bUsePawnControlRotation = true;

	//22.12.19 add
	SpringArm->SocketOffset = FVector( 0, 60, 0 );

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstanceConstant* bodyMaterial;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>( &bodyMaterial,
		"MaterialInstanceConstant'/Game/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'" );
	BodyMaterial = UMaterialInstanceDynamic::Create( bodyMaterial, this );


	UMaterialInstanceConstant* logoMaterial;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>( &logoMaterial,
		"MaterialInstanceConstant'/Game/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'" );
	LogoMaterial = UMaterialInstanceDynamic::Create( logoMaterial, this );

	GetMesh()->SetMaterial( 0, BodyMaterial );
	GetMesh()->SetMaterial( 1, LogoMaterial );

	// 22.12.16 added
	Rifle = ACRifle::Spawn( GetWorld(), this );
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
	PlayerInputComponent->BindAction( "Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle );
	PlayerInputComponent->BindAction( "Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim );
	PlayerInputComponent->BindAction( "Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim );
}

void ACPlayer::ChangeColor( FLinearColor inColor )
{
	BodyMaterial->SetVectorParameterValue( "BodyColor", inColor );
	LogoMaterial->SetVectorParameterValue( "BodyColor", inColor );
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

void ACPlayer::OnRifle()
{
	CLog::Log( Rifle->GetEquipped() );
	CLog::Log( Rifle->GetEquipping() );

	if ( Rifle->GetEquipped() )
	{
		Rifle->Unequip();
		CLog::Log( Rifle->GetEquipped() );
		CLog::Log( Rifle->GetEquipping() );
		return;
	}
	Rifle->Equip();

	CLog::Log( Rifle->GetEquipped() );
	CLog::Log( Rifle->GetEquipping() );
}

void ACPlayer::OnAim()
{
	CheckFalse( Rifle->GetEquipped() );
	CheckTrue( Rifle->GetEquipping() );

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	
	SpringArm->TargetArmLength = 100;
	SpringArm->SocketOffset = FVector( 0, 30, 10 );
	Camera->FieldOfView = 45;
}

void ACPlayer::OffAim()
{
	CheckFalse( Rifle->GetEquipped() );
	CheckTrue( Rifle->GetEquipping() );

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector( 0, 0, 0 );
	Camera->FieldOfView = 90;
}
