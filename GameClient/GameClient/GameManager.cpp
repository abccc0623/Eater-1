#pragma
#include "MainHeader.h"
#include "GameManager.h"
#include "intro.h"

#pragma comment (lib,"../lib/EaterEngine")
GameManager::GameManager()
{
}

GameManager::~GameManager()
{

}

void GameManager::Start(HWND _g_hWnd)
{
	//���� �ʱ�ȭ (�Ŵ����� ����)
	StartEngine(_g_hWnd);
	
	//��ũ���� ����
	CreateScene("Intro", Intro_Awake, Intro_Start, Intro_Update, Intro_End);
	CreateScene("InGame", InGame_Awake, InGame_Start, InGame_Update, InGame_End);

	ChoiceScene("InGame");
	StartScene();
}

void GameManager::Update()
{
	//�Ѱ��� ��ũ�� �������� ��ũ���� ������Ʈ�� ������
	UpdateEngine();
}