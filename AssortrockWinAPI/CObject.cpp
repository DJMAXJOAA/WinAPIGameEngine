#include "pch.h"
#include "CObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr) // ���� �ݶ��̴� ����
	, m_bAlive(true)
{
	m_pCollider = new CCollider(*_origin.m_pCollider); // �ݶ��̴� ���� ����
	m_pCollider->m_pOwner = this;
}

CObject::~CObject()
{	  m_bAlive;	
	// ������Ʈ ������ �־����� �������ֱ�
	if (m_pCollider != nullptr)
		delete m_pCollider;
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->SetOwner(this); // �ֹ� ����
}

void CObject::FinalUpdate()
{
	if (m_pCollider != nullptr)
		m_pCollider->FinalUpdate();
}

void CObject::Render(HDC hdc)
{
	Rectangle(hdc, (int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f),
				   (int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));

	// �ݶ��̴��� �ִ� �� ��ü�� Render ������ �κп� �־��ش�
	ComponetRender(hdc);
}

void CObject::ComponetRender(HDC hdc)
{
	// �浹ü�� �ִ� ���, �������̵��� ������Ʈ�� Render() �κп��� �޼��带 ȣ��
	if (m_pCollider != nullptr)
	{
		m_pCollider->Render(hdc);
	}
}

