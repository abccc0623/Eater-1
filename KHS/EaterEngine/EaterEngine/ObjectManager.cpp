#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"

/// �ӽ� ���� �߰�.
#include "DH3DEngine.h"


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

void ObjectManager::AllDeleteObject()
{
	//���� �Լ� ������ ����Ʈ ����
	AwakeFunction.Clear();
	StartFunction.Clear();

	//������Ʈ �Լ� ������ ����Ʈ ����
	StartUpdate.Clear();
	Update.Clear();
	EndUpdate.Clear();
}

void ObjectManager::PushStartUpdate(Component* mComponent)
{
	//���۳�Ʈ���� ������Ʈ �Լ��� ��Ƴ��� ����Ʈ�� ���� ���۳�Ʈ ������Ʈ �Լ��� �־���
	StartUpdate.Push(mComponent, std::bind(&Component::StartUpdate, mComponent));
}

void ObjectManager::PushUpdate(Component* mComponent)
{
	Update.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushEndUpdate(Component* mComponent)
{
	//���� �������� ����Ǵ� ������Ʈ �Լ�����Ʈ�� �ִ´�
	EndUpdate.Push(mComponent, std::bind(&Component::EndUpdate, mComponent));
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
	Update.Play();

	//���� �������� ����Ǵ� Update �Լ� ����Ʈ
	DebugManager::GM()->Print("->FinalUpdate ����\n");
	EndUpdate.Play();

	///������ �۾��� ���⼭?
	
	








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
	Update.Clear();
}

void ObjectManager::DeleteObject()
{
	//������ ������Ʈ ��ŭ �ݺ����� ����
	for (unsigned i = 0; i < DeleteList.size(); i++)
	{
		//ť���� ����������� ������Ʈ�� ������
		GameObject* temp = DeleteList.front();
		int count = temp->GetComponentCount();
		for (int j = 0; j < count; j++)
		{
			Component* cpt = temp->GetDeleteComponent(j);
			//���۳�Ʈ ���� �Լ������� ����Ʈ���� �����۳�Ʈ�� �Լ������͸�ã�Ƽ� ����
			DeleteComponent(cpt);
		}

		//���� ������ ������ ����Ʈ������ ���ش�
		DeleteList.pop();
	}
}

void ObjectManager::DeleteComponent(Component* cpt)
{
	if (cpt->FUNCTION_MASK & AWAKE)
	{
		AwakeFunction.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & START)
	{
		StartFunction.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & START_UPDATE)
	{
		StartUpdate.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & UPDATE)
	{
		Update.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & END_UPDATE)
	{
		EndUpdate.Pop(cpt);
	}

	///���ʿ��� ������ �Լ������Ϳ� �־��� ���� ������Ű�� �ɵ�




	///��¥ ���۳�Ʈ ����
	delete cpt;
	cpt = nullptr;
}

