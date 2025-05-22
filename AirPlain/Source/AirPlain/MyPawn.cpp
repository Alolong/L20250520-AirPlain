// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"//경로 중 제일 뒤엣것만 쓰면된다.// 특이 경로는 외우기
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h" //카메라는 위치 다름
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyActor.h"
#include "Kismet/GameplayStatics.h"
//전방선언



// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // bool형 체크박스 ,소문자b 앞에 씀  
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box; 

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box); // 박스에 붙이기

	

	//생성자에서만 동작
	// 스태틱 메시 컴포넌트에 스태틱 메시를 불러오기
	// 
	//	static 그래픽자료형 변수(TEXT("경로"));
	//ConstructorHelpers 에 있는 FObjectFinde 자료형 // SMbody 변수명 ///생성자 text
	//모델링 불러올 때는 UStaticMesh로 - Component아님 주의
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SM_P38_Body.SM_P38_Body'"));

	if (SM_Body.Succeeded()) //  성공이니?
	{
		Body->SetStaticMesh(SM_Body.Object);
	}
		
	//////////////////////////////////////////////////////////////
	
	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Box); // 박스에 붙이기

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Box); // 박스에 붙이기


	//프로펠러 스태틱메시를 컴포넌트에 부르고 FVector 위치에 놓기
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(37.571327f, -21.000000f, 1.328775f));
	Right->SetRelativeLocation(FVector(37.571327f, 21.000000f, 1.328775f));








	///////////////////////////////////////////////////////




	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box); // 박스에 붙이기
	
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box); // 박스에 붙이기
	SpringArm->TargetArmLength = 120.0f;// 길이
	SpringArm->bEnableCameraLag = true; //카메라 랙 (체크박스)
	SpringArm->bEnableCameraRotationLag = true;//카메라 로테이션 랙 (체크박스


	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm); // 박스에 붙이기






	//변수 초기화
	Boost = 0.5f;
	MoveSpeed = 10.0f;
	RotateSpeed = 60.0f;

	Movement->MaxSpeed = MoveSpeed;//할당 안됨
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


//Claude, LLM 코드 생성
// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), Boost);

	//프로펠러 회전
	Left->AddLocalRotation(FRotator(0, 0, 7200 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
	Right->AddLocalRotation(FRotator(0, 0, 7200 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));



}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent:: IE_Released ,this,& AMyPawn::Fire);
	PlayerInputComponent->BindAction(TEXT("Boost"), EInputEvent::IE_Released, this, &AMyPawn::DoBoost);
	PlayerInputComponent->BindAction(TEXT("UnBoost"), EInputEvent::IE_Released, this, &AMyPawn::UnBoost);

		
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, & AMyPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::AddControllerPitchInput);
}


void AMyPawn::Fire()
{
	//문법 : CDO 포인터를 가리킴 
	//의미 : 클래스 이름을 저장하고 싶다.
	RocketTemplate = AMyActor :: StaticClass();
	GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), Arrow->K2_GetComponentToWorld());

	



}

void AMyPawn::Roll(float Value)
{
	//AddActorLocalRotation(FRotator DeltaRotation, bool bSweep, FHitResult* OutSweepHitResult, ETeleportType Teleport) 
	//AddActorLocalRotation(FRotator(0, 0, 0)) 
	//Roll 하는 값  = FMath::Clamp(Value, -1.0f, 1.0f) * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())
	// clamp 범위 설정 * RotateSpeed변수 * 월드 델타세컨드 

	AddActorLocalRotation(FRotator(0, 
		0,
		FMath::Clamp(Value, -1.0f, 1.0f) * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

void AMyPawn::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(FMath::Clamp(Value, -1.0f, 1.0f) * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0, 0));
}

void AMyPawn::DoBoost()
{
	Boost = 1.0f;
}

void AMyPawn::UnBoost()
{
	Boost = 0.5f;
}
