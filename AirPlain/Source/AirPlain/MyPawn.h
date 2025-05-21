// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"



class UBoxComponent; // 전방선언  include와 Uclass 사이
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UFloatingPawnMovement;


UCLASS()
class AIRPLAIN_API AMyPawn : public APawn
{
	GENERATED_BODY()

	
public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



UPROPERTY(VisibleAnywhere,Category = "Components",BlueprintReadOnly)//이 뒤에는 언리얼에서 사용하는 프로퍼티
//VisibleAnywhere는 현재 이 변수를 어디서나 볼 수 있음-보통 컴포넌트
// EditAnywhere - 현재 이 변수를 어디서나 조작할 수 있음
// Category - 변수의 항목을 나눠서 들어감
// BlueprintReadOnly - 겟만 할 수 있음
	//TObjectptr<UBoxComponent> Box ; 이-> 언리얼에서 관리
TObjectPtr<UBoxComponent> Box; //  언리얼의 박스 컴포넌트  항상 포인터 사용한다. UBoxComponent 형 Box

UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadWrite)
 TObjectPtr<UStaticMeshComponent>  Body;

 
UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
TObjectPtr <UStaticMeshComponent> Left;
 

UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
TObjectPtr <UStaticMeshComponent> Right;

UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
TObjectPtr< USpringArmComponent > SpringArm;

UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
TObjectPtr< UCameraComponent > Camera;

UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
TObjectPtr< UArrowComponent > Arrow;

UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly)
TObjectPtr< UFloatingPawnMovement > Movement;


 // 변수생성
 UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
 float MoveSpeed;

 UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
 float RotateSpeed;

 UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
 float Boost = 0.5f;

};
