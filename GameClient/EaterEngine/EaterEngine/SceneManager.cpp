#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"
SceneManager::SceneManager()
{
	NowScene = nullptr;
}

SceneManager::~SceneManager()
{
	
}



void SceneManager::CreateScene(std::string name, void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)())
{
	Scene* temp = new Scene();
	temp->Name = name;
	temp->PushFunction(mAwake, mStart, mUpdate, mEnd);
	SceneList.insert({ name,temp });
}

void SceneManager::ChoiceScene(std::string SceneName)
{
	if (SceneList.find(SceneName) == SceneList.end())
	{
		//ã�� ������ ��� �����ڵ�
	}

	NowScene = SceneList[SceneName];


	//ObjectManager::GM()->PlayStart();
}

 
void SceneManager::Delete()
{
	NowScene = nullptr;
	//��� ��ũ�� ����
	SceneList.clear();
}


void SceneManager::SceneStart()
{
	NowScene->Awake();
	NowScene->Start();
}

void SceneManager::SceneUpdate()
{
	//��ũ�� ���� ������Ʈ�ϰ� �״��� ���۳�Ʈ�� ������Ʈ
	NowScene->Update();
	///��������?
}
