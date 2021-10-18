#include "MainHeader.h"
#include "Scene.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "DebugManager.h"
#include "Delegate.h"
#include "Component.h"
#include "Transfrom.h"
#include "ObjectManager.h"

SceneManager*	gSceneManager;
DebugManager*	gDebugManger;
ObjectManager*	gObjectManager;

//���� ����
EATER_ENGINEDLL void StartEngine()
{
	//��ũ�� �Ŵ��� ����
	gSceneManager	= new SceneManager();
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
EATER_ENGINEDLL GameObject* CreateGameObject()
{
	GameObject* temp = new GameObject();
	ObjectManager::GM()->PushCreateObject(temp);
	return temp;
}

//���� ������Ʈ ����
EATER_ENGINEDLL void DeleteGameObject(GameObject* obj)
{
	ObjectManager::GM()->PushDeleteObject(obj);
}

//������ ��ũ�� ����
EATER_ENGINEDLL void ChoiceScene(std::string name)
{
	gSceneManager->ChoiceScene(name);
}

EATER_ENGINEDLL void StartScene()
{
	gSceneManager->SceneStart();
	ObjectManager::GM()->PlayStart();
}

EATER_ENGINEDLL void CreateScene(std::string name, void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)())
{
	gSceneManager->CreateScene(name, mAwake,mStart,mUpdate,mEnd);
}


