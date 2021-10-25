
#include "MainHeader.h"
#include "Scene.h"
#include "GameObject.h"
#include "Delegate.h"
#include "Component.h"
#include "Transfrom.h"
#include "MeshFilter.h"
#include "KHParser.h"
#include "SceneManager.h"
#include "DebugManager.h"
#include "ObjectManager.h"
#include "LoadManager.h"

SceneManager* gSceneManager;
DebugManager* gDebugManger;
ObjectManager* gObjectManager;
LoadManager* gLoadManager;



//���� ����
EATER_ENGINEDLL void StartEngine(HWND _g_hWnd)
{
	//��ũ�� �Ŵ��� ����
	gSceneManager = new SceneManager();
	gLoadManager = new LoadManager();

	/// <summary>
	/// ��¥ �׽�Ʈ��..
	/// </summary>
	MeshFilter::hWnd = _g_hWnd;

	//�ʱ�ȭ
	gLoadManager->init();
	DebugManager::GM()->init();
}

//���� ����
EATER_ENGINEDLL void EndEngine()
{
	gSceneManager->Delete();
	gDebugManger->Delete();
}

//���� ������Ʈ
EATER_ENGINEDLL void UpdateEngine()
{
	//�Լ� �����͸���Ʈ�� ����
	gSceneManager->SceneUpdate();
	ObjectManager::GM()->PlayUpdate();
}

//���� ������Ʈ ����
EATER_ENGINEDLL GameObject* Instance()
{
	GameObject* temp = new GameObject();
	ObjectManager::GM()->PushCreateObject(temp);
	return temp;
}

//���� ������Ʈ ����
EATER_ENGINEDLL void Destroy(GameObject* obj)
{
	ObjectManager::GM()->PushDeleteObject(obj);
}

//������ ��ũ�� ����
EATER_ENGINEDLL void ChoiceScene(std::string name)
{
	gSceneManager->LoadScene(name);
}

EATER_ENGINEDLL void StartScene()
{
	gSceneManager->SceneStart();
	ObjectManager::GM()->PlayStart();
}

EATER_ENGINEDLL Scene* CreateScene(std::string name)
{
	return  gSceneManager->CreateScene(name);
}

EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale,bool LoadAnime)
{
	gLoadManager->LoadMesh(mMeshName, Scale,LoadAnime);
}

EATER_ENGINEDLL void LoadMeshPath(std::string mPath)
{
	gLoadManager->LoadMeshPath(mPath);
}

EATER_ENGINEDLL void GetMeshFilter(std::string mMeshName, MeshFilter* Filter)
{
	FBXModel*  temp = gLoadManager->GetMesh(mMeshName);
	Filter->SetMeshName(mMeshName);
	Filter->SetBuffer(temp);
}

