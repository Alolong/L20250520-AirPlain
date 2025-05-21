// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"
//CDO 초기 기본값 - 생성자 new를 쓰지 않는다.
AMyGameModeBase::AMyGameModeBase()
{

	UE_LOG(LogTemp, Warning, TEXT("Hello World")); // 로그 작성 외우기

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, TEXT("Hello World!"));
	}


	PlayerControllerClass = AMyPlayerController::StaticClass();// playercontroller 붙이기
	DefaultPawnClass = AMyPawn::StaticClass();//mypawn 붙이기 static class미리 만들어진 걸 사용

}
