// Fill out your copyright notice in the Description page of Project Settings.

#include "FItemCreater.h"
#include "FItemManager.h"

#include "Classes/Components/TextRenderComponent.h"
#include "Classes/Components/ArrowComponent.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values
AFItemCreater::AFItemCreater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->XScale = 3.f;
	Text->YScale = 3.f;
	Text->SetRelativeRotation(FRotator(90.f, -180.f, 0.f));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetVisibility(true);
}

// Called when the game starts or when spawned
void AFItemCreater::BeginPlay()
{
	Super::BeginPlay();

	AFItemManager::CreateItem(this, UKismetStringLibrary::Conv_StringToName(UKismetTextLibrary::Conv_TextToString(Text->Text)));
	Destroy();
}

// Called every frame
void AFItemCreater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

