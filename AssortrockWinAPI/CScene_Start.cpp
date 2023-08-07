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
	CScene::Update();	// 부모쪽 함수를 이용할 수도 있음, 오버라이딩 한 이유는 +@ 하기 위해서
	
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void CScene_Start::Enter()
{
	// Player 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(320.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// Player의 복사 생성
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

	// Monster 추가
	int iMonCount = 16;
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	CMonster* pMonsterObj = nullptr;

	float fTerm = (vResolution.x - (75.f * 2)) / (float)(iMonCount-1); // 몬스터 사이의 간격
	for (int i = 0; i < iMonCount; i++)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2(75.f + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetScale(Vec2(50.f, 50.f));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// 충돌 처리 -> player 그룹과 monster 그룹 간의 충돌 체크
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
