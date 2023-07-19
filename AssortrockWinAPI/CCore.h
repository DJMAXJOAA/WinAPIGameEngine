#pragma once
// 싱글톤 : 두가지 방법 -> 데이터 영역 사용, 동적 할당

class CCore
{
	SINGLE(CCore);
private:
	HWND    m_hWnd;			// 메인 윈도우 핸들
	POINT   m_ptResolution;	// 해상도 정보
	HDC		m_hDC;			// 메인 윈도우에 Draw할 DC

	HBITMAP	m_hBit;
	HDC		m_memDC;		// 더블 버퍼링

public:
	int Init(HWND hWnd, POINT ptResolution);
	void Progress();

public:
	HWND GetMainhWnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }

private:
	CCore();
	~CCore();
};
