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
#include "CAnimator.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// �ݶ��̴� ��� + �ݶ��̴� ����
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(30.f, 50.f));

	m_pTex = CResMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\asdf2.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player", m_pTex, Vec2(0.f, 0.f), Vec2(170.f, 179.f), Vec2(171.f, 0.f), 5); // 854x179, 170x179 5���� + ����1ĭ����
}

// ������ ���� ��Ұ� �ؽ�ó -> ���� �����ؿ;� �ϴ� ��Ҵϱ�, ���� ��������ڸ� �Ű澵 �ʿ䰡 ����
//CPlayer::CPlayer(const CPlayer& _origin)
//	: CObject(_origin)
//	, m_pTex(_origin.m_pTex) 
//{
//}

CPlayer::~CPlayer()
{

}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(-0.f, -1.f)); // ���� ����

	// �ٷ� ��������� �ʰ�, �̺�Ʈ �Ŵ������� �̺�Ʈ�� �߰���Ŵ
	// ���� �����ӿ� �����������
	CreateObj(pMissile, GROUP_TYPE::MISSILE_PLAYER);
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
}

