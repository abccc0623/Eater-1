#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
#include "Component.h"
#include "../SharedData.h"

/// <summary>
/// ������ �Ž������� �ļ����� �޾ƿ��� �����صδ� ���۳�Ʈ
/// ����� �׽�Ʈ���̴� �ٽø����� �Ҽ�������
/// </summary>
class FBXModel;
class DH3DEngine;
class MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	// Component��(��) ���� ��ӵ�
	virtual void Awake() override;

	virtual void Start() override;

	virtual void Update() override;


	static HWND hWnd;
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);
	EATER_ENGINEDLL void SetBuffer(FBXModel* Model);
private:
	std::string MeshName;
	FBXModel* MeshFilterData;


	DH3DEngine* pTest_Engine;
	OneFrameData* pTest_OFD;
	SharedRenderData* pTest_SRD;
	DHParser::Mesh* pTest_Mesh;
};

