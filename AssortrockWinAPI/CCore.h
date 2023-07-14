#pragma once
// 싱글톤 : 두가지 방법 -> 데이터 영역 사용, 동적 할당

class CCore
{
	SINGLE(CCore);
private:
	HWND    m_hWnd;			// 메인 윈도우 핸들
	POINT   m_ptResolution;	// 해상도 정보
	HDC		m_hDC;			// 메인 윈도우에 Draw할 DC

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
