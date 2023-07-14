#pragma once
// �̱��� : �ΰ��� ��� -> ������ ���� ���, ���� �Ҵ�

class CCore
{
	SINGLE(CCore);
private:
	HWND    m_hWnd;			// ���� ������ �ڵ�
	POINT   m_ptResolution;	// �ػ� ����
	HDC		m_hDC;			// ���� �����쿡 Draw�� DC

public:
	int Init(HWND hWnd, POINT ptResolution);
	void Progress();

private:
	void Update();
	void Render();

private:
	CCore();
	~CCore();
};
