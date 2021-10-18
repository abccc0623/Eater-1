#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"

ObjectManager* ObjectManager::instance = nullptr;
ObjectManager* ObjectManager::GM()
{
	if (instance == nullptr)
	{
		instance = new ObjectManager();
	}

	return instance;
}

ObjectManager::ObjectManager()
{


}

ObjectManager::~ObjectManager()
{


}

void ObjectManager::PushCreateObject(GameObject* obj)
{
	//������Ʈ�� �־��ٶ� ����� �ִ������� Ȯ��
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		if ( (*it) == nullptr)
		{
			//����� ã�Ҵٸ� ����� �־��ְ� �Լ� ����
			(*it) = obj;
			return;
		}
	}

	//����̾��ٸ� �׳� �־���
	ObjectList.push_back(obj);
}

void ObjectManager::PushDeleteObject(GameObject* obj)
{
	//������Ʈ�� �־��ٶ� ����� �ִ������� Ȯ��
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		//������ ������Ʈ�� ã�Ҵٸ� �׿�����Ʈ�� �ϴ� ����Ʈ���� ����
		if ((*it) == obj)
		{
			GameObject* temp = (*it);
			(*it) = nullptr;

			//������ ����Ʈ�� �־��ش�
			DeleteList.push(temp);
		}
	}
}

void ObjectManager::PushStartUpdate(Component* mComponent)
{
	//���۳�Ʈ���� ������Ʈ �Լ��� ��Ƴ��� ����Ʈ�� ���� ���۳�Ʈ ������Ʈ �Լ��� �־���
	StartUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushDefaultUpdate(Component* mComponent)
{
	DefaultUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushFinalUpdate(Component* mComponent)
{
	//���� �������� ����Ǵ� ������Ʈ �Լ�����Ʈ�� �ִ´�
	FinalUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushStart(Component* mComponent)
{
	StartFunction.Push(mComponent, std::bind(&Component::Start, mComponent));
}

void ObjectManager::PushAwake(Component* mComponent)
{
	AwakeFunction.Push(mComponent, std::bind(&Component::Awake, mComponent));
}

void ObjectManager::PlayUpdate()
{
	DebugManager::GM()->Print("////////////Update////////////\n");

	//���� ��������Ǵ� StartUpdate �Լ� ����Ʈ
	DebugManager::GM()->Print("->StartUpdate ���� \n");
	StartUpdate.Play();
	
	//�߰� �ܰ迡 ����Ǵ� Update �Լ� ����Ʈ
	DebugManager::GM()->Print("->DefaultUpdate ����\n");
	DefaultUpdate.Play();

	//���� �������� ����Ǵ� Update �Լ� ����Ʈ
	DebugManager::GM()->Print("->FinalUpdate ����\n");
	FinalUpdate.Play();

	///������






	///����
	DeleteObject();
}

void ObjectManager::PlayStart()
{
	DebugManager::GM()->Print("////////////start////////////\n");
	DebugManager::GM()->Print("->Awake ���� \n");
	AwakeFunction.Play();
	DebugManager::GM()->Print("->Start ���� \n");
	StartFunction.Play();
}

void ObjectManager::ClearFunctionList()
{
	StartUpdate.Clear();
	FinalUpdate.Clear();
}

void ObjectManager::DeleteObject()
{
	//������ ������Ʈ ��ŭ �ݺ����� ����
	for (unsigned i = 0; i < DeleteList.size(); i++)
	{
		//ť���� ����������� ������Ʈ�� ������
		GameObject* temp = DeleteList.front();

		for (int j = 0; j < temp->GetComponentCount(); j++)
		{
			Component* cpt = temp->GetDeleteComponent();

			//���۳�Ʈ ���� �Լ������� ����Ʈ���� �����۳�Ʈ�� �Լ������͸�ã�Ƽ� ����
			DeleteComponent(cpt);

			//���� ������ ������ ����Ʈ������ ���ش�
			DeleteList.pop();
		}
	}
}

void ObjectManager::DeleteComponent(Component* cpt)
{
	//���۴ܰ��� �Լ������Ϳ��� �־���� �Լ����� ����
	AwakeFunction.Pop(cpt);
	StartFunction.Pop(cpt);


	int state = cpt->GetUpdateState();
	//���۳�Ʈ�� � ������Ʈ �Լ��������� ���ִ��� Ȯ���ϰ� ����
	switch (state)
	{
	case (int)COMPONENT_STATE::DEFAULT_UPDATE:
		DefaultUpdate.Pop(cpt);
		break;
	case (int)COMPONENT_STATE::START_UPDATE:
		StartUpdate.Pop(cpt);
		break;
	case (int)COMPONENT_STATE::END_UPDATE:
		FinalUpdate.Pop(cpt);
		break;
	}

	///���ʿ��� ������ �Լ������Ϳ� �־��� ���� ������Ű�� �ɵ�






	///��¥ ���۳�Ʈ ����
	delete cpt;
}
