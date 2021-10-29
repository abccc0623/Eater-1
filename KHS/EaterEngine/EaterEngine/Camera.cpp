#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

std::vector<Camera*> Camera::CamList;
Camera* Camera::MainCam = nullptr;

DirectX::XMMATRIX Camera::mProj_M;
Camera::Camera()
{
	tranform = nullptr;
	mFovY = 0.5f * 3.141592f;
	mAspect = 1;
	mNearZ = 0.1f;
	mFarZ = 4000.0f;
	mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f * mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f * mFovY);

	PushCamList();
}

Camera::~Camera()
{

}

void Camera::Awake()
{
	//오브젝트의 컨퍼넌트 가져오기
	tranform = gameobject->GetComponent<Transform>();
	CreateProj();
}

void Camera::Update()
{
	CreateView();
}

DirectX::XMMATRIX* Camera::GetProj()
{
	return &mProj_M;
}

void Camera::ChoiceMainCam()
{
	MainCam = this;
}

DirectX::XMMATRIX* Camera::GetView()
{
	return &mView_M;
}

DirectX::XMMATRIX* Camera::GetMainView()
{
	return MainCam->GetView();
}

void Camera::CreateProj(float fovY, float aspect, float zn, float zf,bool viewPoint)
{
	///모르면 MSDN 참고 
	///XMMatrixPerspectiveFovLH 함수 검색하면됨

	//시야각
	mFovY	= fovY;
	//뷰 공간 X:Y 가로세로비율
	mAspect = aspect;
	//근접평면 까지의 거리 0보다 커야됨
	mNearZ	= zn;
	//먼 평면 까지의 거리 0보다 커야됨
	mFarZ	= zf;


	mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f * mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f * mFovY);
	
	if (viewPoint == false)
	{
		//원근 투영
		mProj_M = DirectX::XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
	}
	else
	{
		//직교 투영
		mProj_M = DirectX::XMMatrixOrthographicLH(mFovY, mAspect, mNearZ, mFarZ);
	}
	XMStoreFloat4x4(&mProj, mProj_M);
}

void Camera::CreateView()
{
	DirectX::XMFLOAT3 r_ = tranform->GetLocalPosition_Right();
	DirectX::XMFLOAT3 u_ = tranform->GetLocalPosition_UP();
	DirectX::XMFLOAT3 l_ = tranform->GetLocalPosition_Look();


	DirectX::XMVECTOR R = XMLoadFloat3(&r_);
	DirectX::XMVECTOR U = XMLoadFloat3(&u_);
	DirectX::XMVECTOR L = XMLoadFloat3(&l_);
	DirectX::XMVECTOR P = XMLoadFloat3(&tranform->Position);


	float x = DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, R));
	float y = DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, U));
	float z = DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, L));


	mView._11 = r_.x;	mView._12 = u_.x;	mView._13 = l_.x; mView._14 = 0;
	mView._21 = r_.y;	mView._22 = u_.y;	mView._23 = l_.y; mView._24 = 0;
	mView._31 = r_.z;	mView._32 = u_.z;	mView._33 = l_.z; mView._34 = 0;
	mView._41 = -x;		mView._42 = -y;		mView._43 = -z;	  mView._44 = 1;

	mView_M = DirectX::XMLoadFloat4x4(&mView);
}

void Camera::PushCamList()
{
	//만약 메인카메라로 지정한놈이없다면 처음생성한놈이 메인카메라다
	if (MainCam == nullptr)
	{
		MainCam = this;
	}

	int count = CamList.size();
	for (int i = 0; i < count; i++)
	{
		if (CamList[i] == nullptr)
		{
			CamList[i] = this;
			CamList[i]->MyIndex = i;
			return;
		}
	}

	//여기로 왔다는것은 리스트가 꽉찼다는 것
	CamList.push_back(this);
	MyIndex = count;
}


