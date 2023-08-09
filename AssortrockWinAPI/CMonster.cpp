#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"

#include "CCollider.h"

CMonster::CMonster()
	: m_vCenterPos(0.f, 0.f)
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHP(5)
{
	// 콜라이더 얻기 + 콜라이더 설정
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		CCamera::GetInstance()->SetVibrateCamera(30.f, 1, 0.02f);
		m_iHP -= 1;
		if(m_iHP < 0)
 			DeleteObj(this);
	}
}

void CMonster::Update()
{

	Vec2 vCurPos = GetPos();

	//// 진행방향으로 시간당 m_fSpeed만큼 이동
	//vCurPos.x += fDT * m_fSpeed * m_iDir;

	//// 방향 이동
	//float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	//if (0.f < fDist)
	//{
	//	m_iDir *= -1;
	//	vCurPos.x += fDist * m_iDir;
	//}

	SetPos(vCurPos);
}
