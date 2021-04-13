#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

