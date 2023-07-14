#include "pch.h"
#include "CTimeMgr.h"

void CTimeMgr::Init()
{
	// ���� ī��Ʈ Ƚ��
	QueryPerformanceCounter(&m_liCurCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_liFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_liCurCount);

	// ���� �������� ī���ð�, ���� �������� ī���� ���� ���̸� ���Ѵ�
	m_dDT = (double)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) /
		(double)m_liFrequency.QuadPart;

	// ����ī��Ʈ ���� ���� ī��Ʈ������ ����(���� ��� ����)
	m_liPrevCount = m_liCurCount;

	++m_iCallCount;
	if (m_dAcc > 1.)
	{
	}
}

CTimeMgr::CTimeMgr()
	: m_liCurCount{}
	, m_liFrequency{}
	, m_liPrevCount{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{
}

CTimeMgr::~CTimeMgr()
{
}