#pragma once

#include <string>
class FBXParser;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();


	//�ʱ�ȭ
	void init();
	//�� �ε�
	void LoadMesh(std::string Name,bool LoadAnime);
private:
	FBXParser* EATER_Parser;
};