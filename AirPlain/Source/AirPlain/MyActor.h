// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

class UProjectileMovementComponent; //전방 클래스 선언
class UBoxComponent;
class UStaticmeshComponent;



UCLASS()
class AIRPLAIN_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	//템플릿<선언한 클래스>  변수명
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
		TObjectPtr<UBoxComponent> Box; // TObject 매크로의 박스 컴포넌트형의 box를 선언

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
		TObjectPtr<UStaticMeshComponent> Body; //TObject 매크로의 박스 컴포넌트형의 box를 선언

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
		TObjectPtr<UProjectileMovementComponent> Movement; //TObject 매크로의 박스 컴포넌트형의 box를 선언
	


		/////////////////////////////////////////////////////////////////////////////////
		//블루프린트에서 호출 가능
		UFUNCTION(BlueprintCallable)
		void Test();
		


		//
		UFUNCTION()
		void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);




		//BlueprintImplementableEvent -> CPP에서는 함수를 구현하지 않음 블루프린트에서만 가능
		//기획자한테 맡기고 싶을때
		UFUNCTION(BlueprintImplementableEvent)

		void CallCPPToExecuteBP(int Damage);


		//BluePrintNativeEvent- 기본 로직은 CPP에서 두지만 블루프린트에서 오버라이드 가능
		//기본 동작은 CPP 블루프린트에서 덮어쓰고 싶을 때
		UFUNCTION(BluePrintNativeEvent)
		void CallCPPToDefaultExecuteBP(int Damage);
		void CallCPPToDefaultExecuteBP_Implemetation(int Damage);

		//



};
	
