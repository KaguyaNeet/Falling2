// Fill out your copyright notice in the Description page of Project Settings.

#include "FBuffManager.h"
#include "FGameInstance.h"
#include "FBuff.h"
#include "FBaseUnit.h"

#include "GameFramework/Actor.h"

UFBuffManager::UFBuffManager()
{
	BuffFunc start = nullptr;
	BuffFunc tick = nullptr;
	BuffFunc end = nullptr;
	Register_BUFF(Incendiary);
}

UFBuffManager* UFBuffManager::GetBuffManager(AActor* caller)
{
	UFBuffManager* manager = nullptr;
	if (UFGameInstance* gameInstance = Cast<UFGameInstance>(caller->GetGameInstance()))
	{
		manager = gameInstance->GetBuffManager();
	}
	return manager;
}

UFBuff* UFBuffManager::CreateBuff(AActor* caller, const FName& name)
{
	UFBuff* buff = nullptr;
	if (UFBuffManager* manager = GetBuffManager(caller))
	{
		if (BuffFuncs* funcs = manager->Funcs.Find(name))
		{
			buff = NewObject<UFBuff>(manager, UFBuff::StaticClass()->GetFName());
			buff->Initialize(funcs->StartFunc, funcs->TickFunc, funcs->EndFunc);
		}
	}
	
	return buff;
}

Implement_BUFF_Start(Incendiary)
{

}
Implement_BUFF_Tick(Incendiary)
{

}
Implement_BUFF_End(Incendiary)
{

}