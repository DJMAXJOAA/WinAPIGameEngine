#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CScene.h"
#include "CMissile.h"

#include "CCollider.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture 로딩
	m_pTex = CResMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	// 콜라이더 얻기 + 콜라이더 설정
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(30.f, 50.f));
}

CPlayer::~CPlayer()
{

}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(-0.f, -1.f)); // 공격 방향

	// 씬 매니저에서 현재 씬을 불러오기
	CScene* pCurScene = CSceneMgr::GetInstance()->GetcurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

void CPlayer::Render(HDC hdc)
{
	// pTex의 반환값은 uint지만, 화면 밖으로 빠져나갈 수 있어서 음수 값도 가능한 int로 받아야 한다
	int iWidth = m_pTex->Width();
	int iHeight = m_pTex->Height();

	Vec2 vPos = GetPos();

	TransparentBlt(hdc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0 
		, iWidth, iHeight
		, RGB(255, 0, 255));

	// 충돌체 렌더링 함수
	ComponetRender(hdc);
}

void CPlayer::Update()
{
	// 지역변수를 getpos로 복사해와서, 나중에 setpos로 적용 시켜주어야 한다
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 400.f * fDT;
	}
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 400.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 400.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 400.f * fDT;
	}

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		CreateMissile();
	}

	SetPos(vPos);

	// 업데이트 끝나고, 정리(콜라이더 처리 등)
	FinalUpdate();
}

