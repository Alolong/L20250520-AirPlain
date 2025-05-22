// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


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
	// static ConstructorHelpers 구조체의 템플릿
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SM_Rocket.SM_Rocket'"));

	if (SM_Body.Succeeded()) //SM_Body가 이식 성공하면
	{
		Body->SetStaticMesh(SM_Body.Object); //Staticmesh를 저장하는 함수 실행 
	}
	Body->SetRelativeRotation(FRotator(-90.0f, 0, 0)); // body의 relativerotation을 저장한다.

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));



	Movement->InitialSpeed = 2000.0f;
	Movement->MaxSpeed = 2000.0f;
	Movement->ProjectileGravityScale = 0.0f;



}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	

	SetLifeSpan(3.0f);
	//OnActorBeginOverlap - AActor의 델리게이트- 다른액터가 이 액터에 오버랩시 발생
	//AddDynamic 동적 델리게이트 바인딩함수(헬퍼 매크로)-위 델리게이트 이벤트가 발생시 소괄호 안의 this(인스턴스)와 함수를 연결해줌
	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessBeginOverlap);

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::Test()
{


}

void AMyActor::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	UGameplayStatics::ApplyDamage(OtherActor,
		100.0f,
		nullptr,
		this,
		UDamageType::StaticClass()
	);


	//상속된 블루프린트에 무슨 함수 있을꺼야. 그걸 기획자가 만들면 난 그걸 알아서 호출께
	//CallCPPToExecuteBP(100);
	CallCPPToDefaultExecuteBP(100);

	Destroy();
}


//기획자가 만들어야 할 함수
void AMyActor::CallCPPToDefaultExecuteBP(int Damage)
{

	UE_LOG(LogTemp, Warning, TEXT("이건 CPP 호출 %d"), Damage);
}

