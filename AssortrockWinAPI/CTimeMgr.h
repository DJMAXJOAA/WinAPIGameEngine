#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_liCurCount;
	LARGE_INTEGER	m_liPrevCount;
	LARGE_INTEGER	m_liFrequency;

	double			m_dDT; // �� �����Ӵ� �ð���
	decltype		m_dAcc; // ���� �ð�
	UINT			m_iCallCount;

public:
	void Init();
	void Update();

public:
	CTimeMgr();
	~CTimeMgr();
};