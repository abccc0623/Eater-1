#pragma once

#include <string>
#include <vector>
#include "ObjectManager.h"
class Component;
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


/// <summary>
/// �⺻ ���� ������Ʈ
/// </summary>
class ObjectManager;
class GameObject
{
public:
	GameObject();
	~GameObject();

	

	EATER_ENGINEDLL void SetActive(bool active);	//��� ���۳�Ʈ ������� ����
	EATER_ENGINEDLL void Delete();					//������Ʈ�� ������
	EATER_ENGINEDLL bool GetDelete();				//������Ʈ �������� üũ


	EATER_ENGINEDLL GameObject* GetChild(std::string Name);	//�ڽİ�ü�� ������
	EATER_ENGINEDLL GameObject* GetChild(int Number);		//�ڽİ�ü�� ������

	//������ ���۳�Ʈ�� ������
	Component* GetDeleteComponent();
	//������Ʈ�� ���۳�Ʈ ������ ������
	int GetComponentCount();
public:
	//���۳�Ʈ�� �߰� ��Ų��
	template<typename T>
	EATER_ENGINEDLL T* AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//���۳�Ʈ�� �����´�
	template<typename T>
	T* GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//�ڽİ�ü���� ã�����ϴ� ���۳�Ʈ���ִٸ� �׿�����Ʈ�� ���۳�Ʈ�� ������
	template<typename T>
	T* GetChildComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);
public:
	std::string Name;			//�̸�
	int			Tag;			//�ױ�
	bool		IsDelete;		//���� ����
private:
	bool IsActive;				//��� ��������
private:
	//���۳�Ʈ ����Ʈ
	std::queue<Component*> ComponentList;
	//�ڽİ�ü ����Ʈ
	//std::vector<GameObject*> ChildList;

};

template<typename T>
inline T* GameObject::AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	T* ConponentBox = new T();
	//������ ���۳�Ʈ�� ����Ʈ�� �ִ´�
	ComponentList.push(ConponentBox);

	//���ۺκ��� Start �Լ��� �־��ش�
	ObjectManager::GM()->PushAwake(ConponentBox);
	ObjectManager::GM()->PushStart(ConponentBox);

	//���۳�Ʈ�� �ɼǿ� ���� ������Ʈ ���������� ���ϴ� �Լ�����Ʈ�� �ִ´�
	switch (ConponentBox->GetUpdateState())
	{
	case 0:
		ObjectManager::GM()->PushDefaultUpdate(ConponentBox);
		break;
	case 1:
		ObjectManager::GM()->PushStartUpdate(ConponentBox);
		break;
	case 2:
		ObjectManager::GM()->PushFinalUpdate(ConponentBox);
		break;
	}



	return ConponentBox;
}

template<typename T>
inline T* GameObject::GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	return NULL;
}

template<typename T>
inline T* GameObject::GetChildComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	return nullptr;
}
