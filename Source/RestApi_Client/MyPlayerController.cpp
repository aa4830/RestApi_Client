#include "MyPlayerController.h"
#include "HttpModule.h"
#include "Http.h"
#include "Json.h"
#include "JsonUtilities.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Your log message here"));
    SendHttpRequest(); // HTTP 요청 보내기
}

void AMyPlayerController::SendHttpRequest()
{
    FHttpModule* Http = &FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AMyPlayerController::OnResponseReceived);
    Request->SetURL("http://3.34.116.91:8401/gameResource.json");
    Request->SetVerb("GET");
    Request->SetHeader("Content-Type", "application/json");

    Request->ProcessRequest();
}

void AMyPlayerController::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseString = Response->GetContentAsString();
        UE_LOG(LogTemp, Log, TEXT("Response: %s"), *ResponseString);

        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseString);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
        {
            // "result" 배열을 가져옵니다.
            const TArray<TSharedPtr<FJsonValue>>* ResultArray;
            if (JsonObject->TryGetArrayField(TEXT("result"), ResultArray))
            {
                // 배열의 각 항목을 반복합니다.
                for (const auto& Item : *ResultArray)
                {
                    TSharedPtr<FJsonObject> ItemObject = Item->AsObject();
                    if (ItemObject.IsValid())
                    {
                        FString Key;
                        FString Value;

                        // 키와 값을 가져옵니다.
                        if (ItemObject->TryGetStringField(TEXT("key"), Key) && ItemObject->TryGetStringField(TEXT("value"), Value))
                        {
                            UE_LOG(LogTemp, Log, TEXT("Key: %s, Value: %s"), *Key, *Value);
                        }
                        else
                        {
                            UE_LOG(LogTemp, Error, TEXT("Key or Value not found in JSON"));
                        }
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Result array not found in JSON"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
    }
}
