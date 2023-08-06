#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

#include "CObject.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	// 자주사용하는 펜 등록했던거 지워주기
	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CCore::CreateBrushPen()
{
	// Hollow Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // 이미 정의되어 있는 브러쉬 -> 할로우 브러쉬(지울 필요없음)

	// RGB Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}


int CCore::Init(HWND hWnd, POINT ptResolution)
{
	m_hWnd = hWnd;
	m_ptResolution = ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// 더블 버퍼링 용도의 비트맵과 DC 만들기
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // 전체 화면 해상도 가져오기
	m_memDC = CreateCompatibleDC(m_hDC); // hdc와 동일한 dc 가져오기

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // dc와 비트맵 지정해 주기(반환값은 픽셀 1, 의미X)
	DeleteObject(hOldBit); // 반환값인 hOldBit(원래 사용하던 비트맵)은 바로 지워준다(존재하는 의미가 없음)

	// 자주 사용되는 브러시와 펜 배열을 생성
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInstance()->Init();
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();

	return S_OK;
}

void CCore::Progress()
{
	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();

	//============
	// 렌더링 과정
	//============

	// 화면 클리어
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 화면 그리기
	CSceneMgr::GetInstance()->Render(m_memDC);

	// 두번째 버퍼에서 첫번째 버퍼(실제로 표시되는 화면)에 복사->붙여넣기
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	/*CTimeMgr::GetInstance()->Render();*/
}

