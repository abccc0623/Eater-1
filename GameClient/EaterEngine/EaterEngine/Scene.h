#pragma once

#include <functional>
#include <string>

/// <summary>
/// ������ �����ʿ��� �����Ҷ� �̸��� �Լ������͵鸸 �Ѱ��ְ� ������������ ��ũ���Ŵ������� ���ش�
/// </summary>
class Scene
{
public:
	Scene();
	virtual ~Scene();

	//��ũ���� �־��ָ� 
	void PushFunction(void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)());
	void Awake();
	void Start();
	void Update();
	void End();

	std::string Name;
private:
	std::function<void()> AwakeFunction;
	std::function<void()> StartFunction;
	std::function<void()> UpdateFunction;
	std::function<void()> EndFunction;
};