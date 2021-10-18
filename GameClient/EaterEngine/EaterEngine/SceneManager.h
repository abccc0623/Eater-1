#pragma once

#include <map>
#include <string>
class Scene;



/// <summary>
/// ��ũ���� ���� ���ִ� ��ũ�� �Ŵ���
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();


	void CreateScene(std::string name, void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)());	//��ũ�� ����
	void ChoiceScene(std::string SceneName);				//��ũ�� ����
	void Delete();								

	void SceneStart();		//��ũ���� Awack Start�Լ��� ����
	void SceneUpdate();		//��ũ���� Update �Լ��� ����
private:
	//���� ��ũ��
	Scene* NowScene;

	//��ũ�� ����Ʈ
	std::map<std::string,Scene*> SceneList;
};