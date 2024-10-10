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
	virtual void BeginPlay() override; // ������ �κ�

private:
	void SendHttpRequest(); // HTTP ��û ������ �Լ�
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful); // ���� ó�� �Լ�
};