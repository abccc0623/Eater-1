#pragma once
#include "windows.h"
#include <queue>
#include "EngineData.h"
/// <summary>
/// ���� �������� �����ϴ� �׷��� ���� �ֻ��� Ŭ����
/// ��Ŭ������ ��ӹ��� �׷��� ������ �����ϸ� �ȴ� 
/// </summary>


class MeshData;
class GlobalData;

class GraphicEngine
{
public:
	GraphicEngine() {};
	virtual ~GraphicEngine() {};


	/// <summary>
	/// ������ �׷��� �����ʿ��� ������ �ϴ°͵�
	/// </summary>

	//���� �����ʿ��� ������ �ڵ��� �Ѱ��ٰ���
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight)= 0;


	///�׷��� ������ ���ӿ������� �ְ��޾ƾ��� �Լ���
	virtual void CreateIndexBuffer(Indexbuffer* buffer)	= 0;		//�ε��� ���۸� ������ش�
	virtual void CreateVertexBuffer(Vertexbuffer* buffer)	= 0;	//���ؽ� ���۸� ������ش�
	virtual void CreateTextureBuffer()  = 0;						//�ؽ��ĸ� ������ش�
	virtual void OnReSize(float Change_Width, float Change_Height) = 0; //��������


	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual void Render(std::queue<MeshData*>* meshList, GlobalData* global) = 0;
};