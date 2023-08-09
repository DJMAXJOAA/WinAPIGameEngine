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
	// �ݶ��̴� ��� + �ݶ��̴� ����
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

	//// ����������� �ð��� m_fSpeed��ŭ �̵�
	//vCurPos.x += fDT * m_fSpeed * m_iDir;

	//// ���� �̵�
	//float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	//if (0.f < fDist)
	//{
	//	m_iDir *= -1;
	//	vCurPos.x += fDist * m_iDir;
	//}

	SetPos(vCurPos);
}
