#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta(PI / 2.f)
	, m_vDir(Vec2(1.f, 1.f))
{
	m_vDir.Normalize(); // 정규화 해놓기

	CreateCollider();
}

CMissile::~CMissile()
{
}

void CMissile::Update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT; // 윈도우 좌표계가 반대라서

	SetPos(vPos);
}

void CMissile::Render(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
				 (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}

