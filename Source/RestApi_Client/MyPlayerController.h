#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class RESTAPI_CLIENT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override; // 수정된 부분

private:
	void SendHttpRequest(); // HTTP 요청 보내는 함수
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful); // 응답 처리 함수
};