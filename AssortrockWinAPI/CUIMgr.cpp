#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"
#include "CScene.h"
#include "CUI.h"

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Update()
{
	CScene* pCurScnce = CSceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScnce->GetGroupObject(GROUP_TYPE::UI);	// ���� �ֻ��� �θ�鸸 UI�� �־��� ����

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];	// vector�� cobject���·� �޾ƿ����� �ٿ�ĳ����

		pUI = GetTargetedUI(pUI);	// ���� ���� ������ UI�� �켱������ Ž���Ѵ�
		if (pUI != nullptr)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{
				pUI->MouseLbtnUp();

				// UI ��ư ������ ��������, �� �ڿ� UI ��ư ������ �þ����� �߰� ȣ��
				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	//// 1. �θ� UI �����ؼ�, ��� �ڽĵ��� �˻��Ѵ� (�ڽ��� �������ϼ���, �θ� �������ϼ��� ����)
	CUI* pTargetUI = nullptr;
	
	// �׻� ����ϴ� �����̳ʵ��̴ϱ�, �̸� ���������� �����ؼ� �������� �����ϰ� �����ٰ� �ݺ��� �ʿ� ���� �������ֱ�
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();	
	vecNoneTarget.clear();	// �Ǻ� ���� ���� ���������� �� ��� �ʱ�ȭ

	queue.push_back(_pParentUI);

	//// 2. BFS�� ���ؼ�, ���� ����� UI���� Ÿ���� �˻� (���� ��ȸ ���)
	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI�� TargetUI���� Ȯ���Ѵ�=====================
		// Ÿ�� UI���߿� �� �켱������ ���� �������� �� ���� ������ �ڽ� UI
		if (pUI->IsMouseOn())
		{
			if (pTargetUI != nullptr)
			{
				// �ڸ� ����ֵ� �־��ֱ�
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}
		
		// ==========================================================

		const vector<CUI*> vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}
	}

	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); i++)
		{
			// Ÿ�� �ƴѾֵ� �̸� ��Ƶΰ� �³׵鸸 ���� ��Ȱ��ȭ ó��
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
