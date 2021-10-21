#pragma once

/// <summary>
/// �Ž�,�ؽ���,��� �׸������ؼ� �ʿ��Ѱ͵��� �ε�
/// </summary>




#include <string>
#include <map>
class FBXParser;
class FBXModel;
class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	//�ʱ�ȭ �� ��� ����
	void init();
public:
	///GET
	//�Ž� ��������
	FBXModel* GetMesh(std::string Name);
	//�ؽ��� ��������
	void GetTexture(std::string Name);
public:
	///Load
	//�� �ε�(��ũ�� �̸�,���� �̸�,������ ����,�ִϸ��̼� ����)
	void LoadMesh(std::string Name, bool Scale = true,bool LoadAnime = false);
	//������ �ε�
	void LoadPrefap(std::string Name);

public:
	///���
	//�Ž� ��� ����
	void LoadMeshPath(std::string mPath);
	//�ؽ��� ���
	void LoadTexturePath(std::string mPath);
private:
	//���� ����ִ� ���
	std::string MeshPath;
	//�ؽ��İ� ����ִ� ���
	std::string TexturePath;
public:
	///Delete
	//����Ʈ���� �Ž������� ����(�޸� ���� ��������,�Ž��� �ʹ����Ƽ� �޸𸮰� �����Ҷ�)
	void DeleteMesh(std::string mMeshName);
	//��� �Ž������� ����
	void DeleteMeshAll();
private:
	///����Ʈ
	//�Ž�
	std::map<std::string,FBXModel*> MeshList;
	//���̴� 
	//�ؽ���

private:
	FBXParser* EATER_Parser;
};