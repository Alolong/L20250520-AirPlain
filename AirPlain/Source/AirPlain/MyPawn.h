// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"



class UBoxComponent; // ���漱��  include�� Uclass ����
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



UPROPERTY(VisibleAnywhere,Category = "Components",BlueprintReadOnly)//�� �ڿ��� �𸮾󿡼� ����ϴ� ������Ƽ
//VisibleAnywhere�� ���� �� ������ ��𼭳� �� �� ����-���� ������Ʈ
// EditAnywhere - ���� �� ������ ��𼭳� ������ �� ����
// Category - ������ �׸��� ������ ��
// BlueprintReadOnly - �ٸ� �� �� ����
	//TObjectptr<UBoxComponent> Box ; ��-> �𸮾󿡼� ����
TObjectPtr<UBoxComponent> Box; //  �𸮾��� �ڽ� ������Ʈ  �׻� ������ ����Ѵ�. UBoxComponent �� Box

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


 // ��������
 UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
 float MoveSpeed;

 UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
 float RotateSpeed;

 UPROPERTY(EditAnywhere, Category = "Data", BlueprintReadWrite)
 float Boost = 0.5f;

};
