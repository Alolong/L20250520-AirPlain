// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values // 생성자
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CreateDefaultSubobject -서브오브젝트생성()
	// 서브오브젝트= 하나의 오브젝트(액터) 내에서 서로다른 부분을 조작할 수 있는 부분들
	// 매크로 <자료형클래스> (TEXT("변수명")); 
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box; //루트

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box); // 박스에 붙이기
	//오브젝트  SM_Body로 붙이기 
	// static ConstructorHelpers 구조체의 매크로
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SM_Rocket.SM_Rocket'"));

	if (SM_Body.Succeeded()) //SM_Body가 이식 성공하면
	{
		Body->SetStaticMesh(SM_Body.Object); //Staticmesh를 저장하는 함수 실행 
	}
	Body->SetRelativeRotation(FRotator(-90.0f, 0, 0)); // body의 relativerotation을 저장하낟.






	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	Movement->InitialSpeed = 2000.0f;
	Movement->MaxSpeed = 2000.0f;
	Movement->ProjectileGravityScale = 0.0f;



}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

