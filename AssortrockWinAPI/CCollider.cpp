#include "pch.h"
#include "CCollider.h"

#include "CCore.h"

#include "CObject.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
{
}

CCollider::CCollider(const CCollider& _origin)
	:m_pOwner(nullptr)					// �ݶ��̴��� ����Ǿ�����, ���� �ִ� ������ ������Ű�� �ȵ�
	,m_vOffsetPos(_origin.m_vOffsetPos)
	,m_vFinalPos(_origin.m_vFinalPos)
	,m_vScale(_origin.m_vScale)			// ������ ����������� �״�� ����
	,m_iID(g_iNextID++)					// ID���� ���� �������� �߰���Ŵ
{

}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	// Object�� ��ġ�� ����
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::Render(HDC hdc)
{
	SelectGDI pen(hdc, PEN_TYPE::GREEN);
	SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW);

	Rectangle(hdc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));
}

void CCollider::OnCollision(CCollider* _pOther)
{

}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
}
