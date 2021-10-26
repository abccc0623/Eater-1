#include "LoadManager.h"
#include "DebugManager.h"
#include "DH3DEngine.h"
#include "KHParser.h"
#include "EngineData.h"

LoadManager::LoadManager()
{
	EATER_Parser = nullptr;
}

LoadManager::~LoadManager()
{

}

void LoadManager::init()
{
	EATER_Parser = new FBXParser();
	EATER_Parser->Initalize();
}

FBXModel* LoadManager::GetMesh(std::string Name)
{
	std::map<std::string, FBXModel*>::iterator temp = MeshList.find(Name);
	if (temp == MeshList.end())
	{
		std::string temp = "[Find]다음 내용의 매쉬를 찾지못했습니다 ->" + Name;
		DebugManager::GM()->Print(temp.c_str());
		return nullptr;
	}

	return temp->second;
}

void LoadManager::GetTexture(std::string Name)
{

}

void LoadManager::LoadMesh( std::string Name, bool Scale, bool LoadAnime)
{
	// "../ 이거와 .fbx 이거를 붙여준다"
	std::string temp = ".fbx";
	std::string FullName = MeshPath + Name + temp;

	//규황이 파서를 통해서 매쉬를 로드
	DebugManager::GM()->Print(FullName.c_str());
	EATER_Parser->LoadScene(FullName.c_str(), Scale, LoadAnime);
	FBXModel* box = EATER_Parser->GetModel();

	//나의 구조체맞게 값을 복사한다
	ChangeData(box);



		
}

void LoadManager::LoadPrefap(std::string Name)
{
	///나중에 구현
}

void LoadManager::LoadMeshPath(std::string mPath)
{
	//모델 경로 입력
	MeshPath = mPath;
}

void LoadManager::LoadTexturePath(std::string mPath)
{
	//텍스쳐 경로 입력
	TexturePath = mPath;
}

void LoadManager::DeleteMesh(std::string mMeshName)
{
	//메모리에 할당한 매쉬의 정보를 삭제시킴

	std::map<std::string, FBXModel*>::iterator temp = MeshList.find(mMeshName);
	if (temp == MeshList.end())
	{
		std::string temp = "[Delete]다음 내용의 매쉬를 찾지못했습니다 ->" + mMeshName;
		DebugManager::GM()->Print(temp.c_str());
		return;
	}
	MeshList.erase(mMeshName);
}

void LoadManager::DeleteMeshAll()
{
	MeshList.clear();
}

void LoadManager::ChangeData(FBXModel* mData)
{
	///로드한 데이터 EaterEngine 데이터 타입에 맞게 변경
	
	//지금은 동혁이 엔진을 참조하여 만들것
	













}


