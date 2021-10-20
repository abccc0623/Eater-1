#pragma once

#include <map>
#include <vector>
#include <queue>

#include <functional>
#include "Delegate_Map.h"
#include "windows.h"
#include "../SharedData.h"


#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


class DH3DEngine;

class GameObject;
class Component;

class ObjectManager
{
public:
	~ObjectManager();

	//������ ������Ʈ�� �־���
	EATER_ENGINEDLL void PushCreateObject(GameObject* obj);

	//������ ������Ʈ�� �־���(���Լ��� �����ų�ܰ迡�� ������Ʈ�� ������������ ������ ���� ��������)
	EATER_ENGINEDLL void PushDeleteObject(GameObject* obj);

	//���� ������Ʈ ����Ʈ�� ����ִ� ������Ʈ�� ���۳�Ʈ ����Ʈ�� ���� ����
	EATER_ENGINEDLL void AllDeleteObject();
	


	/// <summary>
	/// ���� �ܰ�
	/// </summary>
	EATER_ENGINEDLL void PushStart(Component* obj);
	EATER_ENGINEDLL void PushAwake(Component* obj);
	
	/// <summary>
	/// ������Ʈ �ܰ�
	/// </summary>
	EATER_ENGINEDLL void PushStartUpdate(Component* obj);
	EATER_ENGINEDLL void PushUpdate(Component* obj);
	EATER_ENGINEDLL void PushEndUpdate(Component* obj);



	//������Ʈ �Լ� ����Ʈ�� �����Ŵ
	void PlayUpdate();
	void PlayStart();
	void init(HWND hwnd);

	//������Ʈ�� ������ �Լ�����Ʈ�� ��� ������
	void ClearFunctionList();
	//�̱��� Ŭ����
	EATER_ENGINEDLL static ObjectManager* GM();
private:
	static ObjectManager* instance;
	ObjectManager();

	DH3DEngine* pTest_Engine;
	OneFrameData* pTest_OFD;
	SharedRenderData* pTest_SRD;
	DHParser::Mesh* pTest_Mesh;

	void TestAddVerTex(float _x, float _y, float _z,
		float N_x, float N_y, float N_z);

	void TestAddIndex(UINT _index);


	std::vector<GameObject*> ObjectList;
	std::queue<GameObject*> DeleteList;


	/// <summary>
	/// ���۴ܰ� �ѹ��� �����
	/// </summary>
	Delegate_Map<Component> AwakeFunction;		//���۴ܰ� ���� ���� ����Ǵ� �Լ�
	Delegate_Map<Component> StartFunction;		//���۴ܰ��� ����Ǵ� �Լ�


	/// <summary>
	/// ������Ʈ �ܰ� �����Ӹ��� ����
	/// </summary>
	Delegate_Map<Component> StartUpdate;		//������� ���۵Ǵ� ������Ʈ
	Delegate_Map<Component> Update;				//����Ʈ  �߰��ܰ��� ���۵Ǵ� ������Ʈ
	Delegate_Map<Component> EndUpdate;			//���� �������� ����Ǵ� ������Ʈ


	/// <summary>
	/// ������ �ܰ��� �����Ӹ��� ���� (���� ����)
	/// </summary>
	//Delegate_Map<Component> StartRender;		//������� ���۵Ǵ� ������
	//Delegate_Map<Component> DefaultRender;	//����Ʈ  �߰��ܰ��� ���۵Ǵ� ������
	//Delegate_Map<Component> FinalUpRender;	//���� �������� ����Ǵ� ������


	//�������� �����Ѵ�
	void DeleteObject();
	void DeleteComponent(Component* cpt);
};