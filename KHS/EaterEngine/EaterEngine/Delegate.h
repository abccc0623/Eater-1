#pragma once
#include <vector>
/// <summary>
/// vector �� �Լ�����Ʈ ����Ʈ
/// </summary>
 
 

template<typename T>
class Delegate
{
public:
	Delegate();
	~Delegate();

private:
	std::vector<void(T)> FunctionList;
};

template<typename T>
inline Delegate<T>::Delegate()
{

}

template<typename T>
inline Delegate<T>::~Delegate()
{

}
