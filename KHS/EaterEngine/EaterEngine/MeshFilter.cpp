#include "MeshFilter.h"
#include "DebugManager.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "KHParser.h"
#include "Transform.h"
#include "EngineData.h"

extern LoadManager* gLoadManager;

std::vector<MeshData*> MeshFilter::MeshList;
MeshFilter::MeshFilter()
{
	MeshFilterData = nullptr;
	MeshName = "";
}

MeshFilter::~MeshFilter()
{
	Meshtemp->FBXData = nullptr;
	delete Meshtemp;
}


void MeshFilter::Start()
{
	transform = gameobject->GetComponent<Transform>();
	if (isLoad == true)
	{
		//�Ž� �����͸� �������ְ�
		Meshtemp = new MeshData;
		Meshtemp->FBXData = gLoadManager->GetMesh(MeshName);

		//��� MeshFiliter�鳢�� �����ϴ� ����Ʈ�� �־��ش�
		MeshList.push_back(Meshtemp);
	}
}

void MeshFilter::EndUpdate()
{
	//��� ������Ʈ�� ������ ���� ���۳�Ʈ�� ������ ������
	Meshtemp->mWorld	= transform->GetWorld();
	Meshtemp->Pos		= transform->Position;
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoad = true;
	MeshName = mMeshName;
}

std::vector<MeshData*>* MeshFilter::GetMeshData()
{
	return &MeshList;
}




