#pragma once

#include <string>
#include <vector>
#include "ObjectManager.h"
#include "Component.h"
#include "EngineData.h"
class Component;
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


#define AWAKE				0x00000001
#define START				0x00000010
#define START_UPDATE		0x00000100
#define Transform_UPDATE	0x00001000
#define Physics_UPDATE		0x00010000
#define UPDATE				0x00100000
#define END_UPDATE			0x01000000



/// <summary>
/// 기본 게임 오브젝트
/// </summary>

class Transform;
class GameObject
{
public:
	GameObject();
	~GameObject();

	EATER_ENGINEDLL void SetActive(bool active);	//모든 컨퍼넌트 기능중지 여부
	EATER_ENGINEDLL void Delete();					//오브젝트를 삭제함
	EATER_ENGINEDLL bool GetDelete();				//오브젝트 삭제여부 체크


	EATER_ENGINEDLL GameObject* GetChild(std::string Name);	//자식객체를 가져옴
	EATER_ENGINEDLL GameObject* GetChild(int Number);		//자식객체를 가져옴

	//삭제할 컨퍼넌트를 가져옴
	Component* GetDeleteComponent(int i);

	//오브젝트의 컨퍼넌트 갯수를 가져옴
	int GetComponentCount();
	
	MeshData* OneMeshData;
public:
	//컨퍼넌트를 추가 시킨다
	template<typename T>
	EATER_ENGINEDLL void AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//컨퍼넌트를 가져온다
	template<typename T>
	EATER_ENGINEDLL T* GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//자식객체에서 찾고자하는 컨퍼넌트가있다면 그오브젝트에 컨퍼넌트를 가져옴
	template<typename T>
	T* GetChildComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);
public:
	std::string Name;			//이름
	int			Tag;			//테그
	bool		IsDelete;		//삭제 여부
protected:
	bool IsActive;				//기능 중지여부
	unsigned int FunctionMask;	//어떤 함수포인터에 넣었는지 여부
private:

	//컨퍼넌트 리스트
	std::vector<Component*> ComponentList;
	//자식객체 리스트
	//std::vector<GameObject*> ChildList;

};

template<typename T>
inline void GameObject::AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	//이함수는 무조건 Component를 상속받은 클래스만 들어올수있다
	//그래서 Component 안에 함수만 사용함

	T* ConponentBox = new T();
	//생성한 컨퍼넌트를 리스트에 넣는다
	ComponentList.push_back(ConponentBox);
	ConponentBox->SetObject(this);
	
	//나중에 이타입으로 찾아서 가져올수있도록 타입 설정
	ConponentBox->ComponentType = typeid(T).hash_code();

	///오버라이딩 확인 각각에맞는 함수포인터 리스트에 넣는다 
	//Awake
	if (&Component::Awake != &T::Awake)
	{
		ObjectManager::PushAwake(ConponentBox);
		ConponentBox->FUNCTION_MASK |= AWAKE;
	}

	//Start
	if (&Component::Start != &T::Start)
	{
		ObjectManager::PushStart(ConponentBox);
		ConponentBox->FUNCTION_MASK |= START;
	}

	//StartUpdate
	if (&Component::StartUpdate != &T::StartUpdate)
	{
		ObjectManager::PushStartUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= START_UPDATE;
	}
	//이동 행렬
	if (&Component::TransformUpdate != &T::TransformUpdate)
	{
		ObjectManager::PushTransformUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= Transform_UPDATE;
	}
	//물리 
	if (&Component::PhysicsUpdate != &T::PhysicsUpdate)
	{
		ObjectManager::PushPhysicsUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= Physics_UPDATE;
	}

	//DefaultUpdate
	if (&Component::Update != &T::Update)
	{
		ObjectManager::PushUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= UPDATE;
	}

	//EndUpdate
	if (&Component::EndUpdate != &T::EndUpdate)
	{
		ObjectManager::PushEndUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= END_UPDATE;
	}
}

template<typename T>
inline T* GameObject::GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	//우진이의 코드를 보고 변경
	//문제점...만약 한개의 오브젝트에 같은 컨퍼넌트 두개가 들어와있다면 어떻게 찾을것인가...

	int count = ComponentList.size();
	for (int i = 0; i < count; i++)
	{
		//현재 컨퍼넌트와 찾고자하는 컨퍼넌트의 타입 비교
		if (ComponentList[i]->ComponentType == typeid(T).hash_code())
		{
			//찾은 컨퍼넌트를 타입변환
			T* temp = dynamic_cast<T*>(ComponentList[i]);
			return temp;
		}
	}


	//만약 찾지못했다면 에러코드를 내보내주면될듯..
	return nullptr;
}

template<typename T>
inline T* GameObject::GetChildComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	return nullptr;
}

