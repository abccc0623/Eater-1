#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include "Component.h"
class Transfrom :public Component
{
public:
	EATER_ENGINEDLL Transfrom();
	virtual ~Transfrom();
	

 	// Component��(��) ���� ��ӵ�
	virtual void Awake();
 	virtual void Start();
	virtual void StartUpdate();
private:


};