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
	
		//블루프린트에서 호출 가능
		UFUNCTION(BlueprintCallable)
		void Test();
		


		//
		UFUNCTION()
		void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

		UFUNCTION(BlueprintImplementableEvent)

		void CallCPPToExcuteBP(int Damage);

		UFUNCTION(BluePrintNativeEvent)

		void CallCPPToDefaultExcuteBP(int Damage);
		void CallCPPToDefaultExcuteBP_Implemetation(int Damage);

		//



};
	
