#pragma once
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
class GameObject;
class Scene;


extern "C"
{
	EATER_ENGINEDLL void StartEngine();		//GameEngine ����
	EATER_ENGINEDLL void EndEngine();		//GameEngine ����
	EATER_ENGINEDLL void UpdateEngine();	//GameEngine ������Ʈ


	EATER_ENGINEDLL GameObject* CreateGameObject();					//������Ʈ ����
	EATER_ENGINEDLL void		DeleteGameObject(GameObject* obj);	//������Ʈ ����


	EATER_ENGINEDLL void ChoiceScene(std::string name);					//��ũ���� �����Ѵ�
	EATER_ENGINEDLL void StartScene();	//��ũ�� �ֱ�

	//��ũ�� ����
	EATER_ENGINEDLL void CreateScene
	(
		std::string name,	//��ũ�� �̸�
		void(*mAwake)(),	//��ũ�� Awake �Լ�������
		void(*mStart)(),	//��ũ�� Start	�Լ�������
		void(*mUpdate)(),	//��ũ�� Update  �Լ�������
		void(*mEnd)()		//��ũ�� End		�Լ�������
	);	

}