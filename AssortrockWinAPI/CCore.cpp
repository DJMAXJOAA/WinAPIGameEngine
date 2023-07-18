#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CObject.h"

CObject g_obj;

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

	// Manager 초기화
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();

	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::Progress()
{
	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();

	// ==========
	// 렌더링 과정
	// ==========

	// 화면 클리어
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 화면 그리기
	CSceneMgr::GetInstance()->Render(m_memDC);

	// 두번째 버퍼에서 첫번째 버퍼(실제로 표시되는 화면)에 복사->붙여넣기
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	// 씬 렌더링
}

void CCore::Update()
{
	Vec2 vPos = g_obj.GetPos();

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 400.f * CTimeMgr::GetInstance()->GetfDT();
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 400.f * CTimeMgr::GetInstance()->GetfDT();
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
	{
		vPos.y -= 400.f * CTimeMgr::GetInstance()->GetfDT();
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		vPos.y += 400.f * CTimeMgr::GetInstance()->GetfDT();
	}

	g_obj.SetPos(vPos);
}

void CCore::Render()
{

}

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}