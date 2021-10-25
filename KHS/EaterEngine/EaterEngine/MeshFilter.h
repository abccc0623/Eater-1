#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include "Component.h"


/// <summary>
/// �Ž������� �ļ����� �޾ƿ��� �����صδ� ���۳�Ʈ
/// </summary>

struct MeshData;
class Transform;
class FBXModel;
class DH3DEngine;
class MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	virtual void Start() override;

	virtual void EndUpdate() override;

	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);


	static std::vector<MeshData*>* GetMeshData();
private:
	//�Ž� �ε忩��
	bool isLoad;

	std::string MeshName;
	FBXModel* MeshFilterData;


	Transform* transform;
	MeshData* Meshtemp;


	static std::vector<MeshData*> MeshList;
};

