#include "Component.h"
#include "Transfrom.h"
#include "DebugManager.h"

Transfrom::Transfrom()
{

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


void Transfrom::StartUpdate()
{
	DebugManager::GM()->Print("Transfrom Update �Լ� ���� \n");
}

