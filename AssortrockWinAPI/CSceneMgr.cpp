#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

void CSceneMgr::Init()
{
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"���� �̸�");

	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter(); // �� ����
}

void CSceneMgr::Update()
{
	// ���� ���� ������Ʈ �ؾߵ�
	m_pCurScene->Update();
	
}

void CSceneMgr::Render(HDC hdc)
{
	// ����
	m_pCurScene->Render(hdc);
}

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}
