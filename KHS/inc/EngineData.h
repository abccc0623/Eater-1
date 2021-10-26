#pragma once
#include "ResourcesData.h"

//�� ���� �Ž����� ���������ʾƵ� �Ǵ°͵�
struct GlobalData
{
	//ī�޶� ������
	DirectX::XMMATRIX mViewMX;
	DirectX::XMMATRIX mProj;
};

struct FBXModel;
//�Ѱ��� �Ž��� �����ϴ� ������
class MeshData
{
public:
	MeshData() {};
	~MeshData() 
	{
		
	};

	//�Ž� ���� ���
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mlocal;
	//Mesh ��ġ��
	DirectX::XMFLOAT3 Pos;

	//�ε���,���ؽ� ����
	Indexbuffer*	IB;
	Vertexbuffer*	VB;
};

 



