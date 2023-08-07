#include "pch.h"
#include "CScene_Start.h"

#include "CCore.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTexture.h"

void CScene_Start::Update()
{
	CScene::Update();	// �θ��� �Լ��� �̿��� ���� ����, �������̵� �� ������ +@ �ϱ� ���ؼ�
	
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void CScene_Start::Enter()
{
	// Player �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(320.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// Player�� ���� ����
	{
		CObject* pOtherPlayer = pObj->Clone();
		pOtherPlayer->SetPos(Vec2(420.f, 384.f));
		AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);
	}
	{
		CObject* pOtherPlayer = pObj->Clone();
		pOtherPlayer->SetPos(Vec2(370.f, 354.f));
		AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);
	}

	// Monster �߰�
	int iMonCount = 16;
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	CMonster* pMonsterObj = nullptr;

	float fTerm = (vResolution.x - (75.f * 2)) / (float)(iMonCount-1); // ���� ������ ����
	for (int i = 0; i < iMonCount; i++)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2(75.f + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetScale(Vec2(50.f, 50.f));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// �浹 ó�� -> player �׷�� monster �׷� ���� �浹 üũ
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::MISSILE_PLAYER, GROUP_TYPE::MONSTER);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInstance()->Reset();
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}
