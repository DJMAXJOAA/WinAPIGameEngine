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
	// Texture �ε�
	m_pTex = CResMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	// �ݶ��̴� ��� + �ݶ��̴� ����
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
	pMissile->SetDir(Vec2(-0.f, -1.f)); // ���� ����

	// �� �Ŵ������� ���� ���� �ҷ�����
	CScene* pCurScene = CSceneMgr::GetInstance()->GetcurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

void CPlayer::Render(HDC hdc)
{
	// pTex�� ��ȯ���� uint����, ȭ�� ������ �������� �� �־ ���� ���� ������ int�� �޾ƾ� �Ѵ�
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

	// �浹ü ������ �Լ�
	ComponetRender(hdc);
}

void CPlayer::Update()
{
	// ���������� getpos�� �����ؿͼ�, ���߿� setpos�� ���� �����־�� �Ѵ�
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

	// ������Ʈ ������, ����(�ݶ��̴� ó�� ��)
	FinalUpdate();
}

