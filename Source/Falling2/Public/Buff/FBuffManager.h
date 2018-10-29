// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBuffManager.generated.h"


#define Declare_BUFF(name) \
	namespace name \
	{ \
		static void BuffEnable_##name(class AFBaseUnit* owner, class AFBaseUnit* adder, class UFBuff* buff, UINT lifetime, UINT level); \
		static void BuffTick_##name(class AFBaseUnit* owner, class AFBaseUnit* adder, class UFBuff* buff, UINT lifetime, UINT level); \
		static void BuffDisable_##name(class AFBaseUnit* owner, class AFBaseUnit* adder, class UFBuff* buff, UINT lifetime, UINT level); \
	} \

#define Register_BUFF(name) \
	enable = &BuffFunction::name::BuffEnable_##name; \
	tick = &BuffFunction::name::BuffTick_##name; \
	disable = &BuffFunction::name::BuffDisable_##name; \
	Funcs.Add(FName(#name), BuffFuncs(enable, tick, disable)); \

#define Implement_BUFF_Enable(name) void BuffFunction::name::BuffEnable_##name(AFBaseUnit* owner, class AFBaseUnit* adder,  UFBuff* buff, UINT lifetime, UINT level)
#define Implement_BUFF_Tick(name) void BuffFunction::name::BuffTick_##name(AFBaseUnit* owner, class AFBaseUnit* adder,  UFBuff* buff, UINT lifetime, UINT level)
#define Implement_BUFF_Disable(name) void BuffFunction::name::BuffDisable_##name(AFBaseUnit* owner, class AFBaseUnit* adder,  UFBuff* buff, UINT lifetime, UINT level)

UCLASS()
class FALLING2_API AFBuffManager : public AActor
{
	GENERATED_BODY()

public:
	using BuffFunc = void(*)(class AFBaseUnit* owner, class AFBaseUnit* adder, class UFBuff* buff, UINT lifetime, UINT level);

	struct BuffFuncs
	{
		BuffFuncs(BuffFunc enable, BuffFunc tick, BuffFunc disable):EnableFunc(enable), TickFunc(tick), DisableFunc(disable){ }
		BuffFunc EnableFunc = nullptr;
		BuffFunc TickFunc = nullptr;
		BuffFunc DisableFunc = nullptr;
	};
	
private:
	TMap<FName, BuffFuncs> Funcs;


public:	
	// Sets default values for this actor's properties
	AFBuffManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** 
	 * Create a buff by buff name
	 * @param caller, Actor that call this function
	 * @param name, Buff name that you want to create
	 * @param owner, owner of the buff
	 * @param adder, adder of the buff
	 * @param level, level of the buff
	 * @param lifetime, life time of the buff
	 * @param buffType, type of the buff
	 * @param canOverlap, can the buff overlap
	 */
	static class UFBuff* CreateBuff(class AActor* caller, const FName& name, class AFBaseUnit* owner, class AFBaseUnit* adder, UINT8 level, UINT8 lifetime, UINT8 buffType, bool canOverlap);

	// Get the buff manager singleton
	static AFBuffManager* GetBuffManager(class AActor* caller);
	
};


namespace BuffFunction
{
	Declare_BUFF(Incendiary);
	Declare_BUFF(Frozen);
}