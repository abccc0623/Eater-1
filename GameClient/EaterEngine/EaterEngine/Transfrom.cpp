#include "Component.h"
#include "Transfrom.h"
#include "DebugManager.h"

Transfrom::Transfrom()
{
	UpDateState = (int)COMPONENT_STATE::START_UPDATE;
}

Transfrom::~Transfrom()
{

}


void Transfrom::Awake()
{
	DebugManager::GM()->Print("Transfrom Awake �Լ� ���� \n");
}

void Transfrom::Start()
{
	DebugManager::GM()->Print("Transfrom Start �Լ� ���� \n");
}

void Transfrom::Update()
{
	DebugManager::GM()->Print("Transfrom Update �Լ� ���� \n");
}
