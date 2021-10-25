#include "MainHeader.h"
#include "Scene.h"
#include "intro.h";
#include "GameObject.h"
#include "MeshFilter.h"
#include "Transfrom.h"

#include "AI.h"

void intro::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../FBXFile/");
	LoadMesh("Table");
	
	
}

void intro::Start()
{
	GameObject* obj = Instance();
	obj->AddComponent<Transfrom>();
	obj->AddComponent<MeshFilter>();
	MeshFilter* temp = obj->GetComponent<MeshFilter>();
	GetMeshFilter("Table", temp);
}

void intro::Update()
{


}

void intro::End()
{


}
