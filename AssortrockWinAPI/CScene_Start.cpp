#include "pch.h"
#include "CScene_Start.h"

#include "CCore.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTexture.h"

void CScene_Start::Enter()
{

	// Player �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(320.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// Monster �߰�
	int iMonCount = 16;
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	CMonster* pMonsterObj = nullptr;

	float fTerm = (vResolution.x - (75.f * 2)) / (float)(iMonCount-1); // ���� ������ ����
	for (int i = 0; i < iMonCount; i++)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2(75.f + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetScale(Vec2(50.f, 50.f));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// �浹 ó�� -> player �׷�� monster �׷� ���� �浹 üũ
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
}

void CScene_Start::Exit()
{
	CCollisionMgr::GetInstance()->Reset();
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}
