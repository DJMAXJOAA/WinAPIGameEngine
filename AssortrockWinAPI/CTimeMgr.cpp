#include "pch.h"
#include "CTimeMgr.h"

void CTimeMgr::Init()
{
	// 현재 카운트 횟수
	QueryPerformanceCounter(&m_liCurCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_liFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_liCurCount);

	// 이전 프레임의 카운팅과, 현재 프레임의 카운팅 값의 차이를 구한다
	m_dDT = (double)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) /
		(double)m_liFrequency.QuadPart;

	// 이전카운트 값을 현재 카운트값으로 갱신(다음 계산 위해)
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