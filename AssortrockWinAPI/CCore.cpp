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

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC �����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // ��ü ȭ�� �ػ� ��������
	m_memDC = CreateCompatibleDC(m_hDC); // hdc�� ������ dc ��������

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // dc�� ��Ʈ�� ������ �ֱ�(��ȯ���� �ȼ� 1, �ǹ�X)
	DeleteObject(hOldBit); // ��ȯ���� hOldBit(���� ����ϴ� ��Ʈ��)�� �ٷ� �����ش�(�����ϴ� �ǹ̰� ����)

	// Manager �ʱ�ȭ
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
	// ������ ����
	// ==========

	// ȭ�� Ŭ����
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// ȭ�� �׸���
	CSceneMgr::GetInstance()->Render(m_memDC);

	// �ι�° ���ۿ��� ù��° ����(������ ǥ�õǴ� ȭ��)�� ����->�ٿ��ֱ�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	// �� ������
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