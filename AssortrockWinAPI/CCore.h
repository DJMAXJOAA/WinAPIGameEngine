#pragma once
// �̱��� : �ΰ��� ��� -> ������ ���� ���, ���� �Ҵ�

class CCore
{
	SINGLE(CCore);
private:
	HWND    m_hWnd;			// ���� ������ �ڵ�
	POINT   m_ptResolution;	// �ػ� ����
	HDC		m_hDC;			// ���� �����쿡 Draw�� DC

	HBITMAP	m_hBit;
	HDC		m_memDC;		// ���� ���۸�

	// ���� ����ϴ� GDI ������Ʈ
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

private:
	CCore();
	~CCore();

public:
	int Init(HWND hWnd, POINT ptResolution);
	void Progress();

public:
	HWND GetMainhWnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

private:
	void CreateBrushPen();
};
