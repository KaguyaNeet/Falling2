// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FBuffManager.generated.h"


#define Declare_BUFF(name) \
	namespace name \
	{ \
		static void BuffStart_##name(class AFBaseUnit* owner, class UFBuff* buff, float value1, float value2); \
		static void BuffTick_##name(class AFBaseUnit* owner, class UFBuff* buff, float value1, float value2); \
		static void BuffEnd_##name(class AFBaseUnit* owner, class UFBuff* buff, float value1, float value2); \
	} \

#define Register_BUFF(name) \
	start = &BuffFunction::name::BuffStart_##name; \
	tick = &BuffFunction::name::BuffTick_##name; \
	end = &BuffFunction::name::BuffEnd_##name; \
	Funcs.Add(FName(#name), BuffFuncs(start, tick, end)); \

#define Implement_BUFF_Start(name) void BuffFunction::name::BuffStart_##name(AFBaseUnit* owner, UFBuff* buff, float value1, float value2)
#define Implement_BUFF_Tick(name) void BuffFunction::name::BuffTick_##name(AFBaseUnit* owner, UFBuff* buff, float value1, float value2)
#define Implement_BUFF_End(name) void BuffFunction::name::BuffEnd_##name(AFBaseUnit* owner, UFBuff* buff, float value1, float value2)

/**
 * 
 */
UCLASS()
class FALLING2_API UFBuffManager : public UObject
{
	GENERATED_BODY()

public:
	using BuffFunc = void(*)(class AFBaseUnit*, class UFBuff*, float, float);

	struct BuffFuncs
	{
		BuffFuncs(BuffFunc start, BuffFunc tick, BuffFunc end):StartFunc(start), TickFunc(tick), EndFunc(end){ }
		BuffFunc StartFunc = nullptr;
		BuffFunc TickFunc = nullptr;
		BuffFunc EndFunc = nullptr;
	};
	
public:
	UFBuffManager();
	
public:
	static class UFBuff* CreateBuff(class AActor* caller, const FName& name, UINT8 lifeTime, UINT8 level, AFBaseUnit* target);
	static UFBuffManager* GetBuffManager(class AActor* caller);


	UParticleSystem* FrozenParticle = nullptr;

private:
	

private:
	TMap<FName, BuffFuncs> Funcs;

	
	
};

namespace BuffFunction
{
	Declare_BUFF(Incendiary);
	Declare_BUFF(Frozen);
}