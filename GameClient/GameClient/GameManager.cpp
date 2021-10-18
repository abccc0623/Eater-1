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

void GameManager::Start()
{
	//���� �ʱ�ȭ (�Ŵ����� ����)
	StartEngine();
	
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