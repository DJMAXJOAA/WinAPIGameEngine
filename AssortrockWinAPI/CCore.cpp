#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

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

	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::Progress()
{
	// �ð�üũ
	//static int callcount = 0;
	//++callcount;
	//static int iPrevCount = GetTickCount();

	//int iCurCount = GetTickCount();
	//if (iCurCount - iPrevCount > 1000)
	//{
	//	iPrevCount = iCurCount;
	//	callcount = 0;
	//}

	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();


	Update();
	Render();
}

void CCore::Update()
{
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 400.f * CTimeMgr::GetInstance()->GetfDT();
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 400.f * CTimeMgr::GetInstance()->GetfDT();
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		vPos.y -= 400.f * CTimeMgr::GetInstance()->GetfDT();
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		vPos.y += 400.f * CTimeMgr::GetInstance()->GetfDT();
	}

	g_obj.SetPos(vPos);
}

void CCore::Render()
{
	// �ι�° ������ ȭ�� �ʱ�ȭ
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// �ι�° ���ۿ��� �׸���
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_memDC,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

	// �ι�° ���ۿ��� ù��° ����(������ ǥ�õǴ� ȭ��)�� ����->�ٿ��ֱ�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
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