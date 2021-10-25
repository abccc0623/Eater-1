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

	//��ġ�� (�������ʿ��� �����Ҷ� ���Ϸ���)
	DirectX::XMFLOAT3 Pos;
};



