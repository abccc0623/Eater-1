#pragma once
#include <DirectXMath.h>

//�� ���� �Ž����� ���������ʾƵ� �Ǵ°͵�
struct GlobalData
{
	//ī�޶� ������
	DirectX::XMMATRIX mViewMX;
	DirectX::XMMATRIX mProj;
};


struct FBXModel;
//�Ѱ��� �Ž��� �����ϴ� ������
struct MeshData
{
	//�Ľ��� ������
	FBXModel* FBXData;
	//World
	DirectX::XMMATRIX mWorld;
	//Mesh ��ġ��
	DirectX::XMFLOAT3 Pos;


	//�ε��� ����
	void* IB;
	//���ؽ� ����
	void* VB;
};



