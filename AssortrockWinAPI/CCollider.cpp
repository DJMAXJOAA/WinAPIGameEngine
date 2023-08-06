#include "pch.h"
#include "CCollider.h"

#include "CCore.h"

#include "CObject.h"

#include "SelectGDI.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	// Object의 위치를 따라감
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
