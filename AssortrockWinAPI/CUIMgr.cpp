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
	const vector<CObject*>& vecUI = pCurScnce->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];	// vector�� cobject���·� �޾ƿ����� �ٿ�ĳ����
		if (pUI->IsMouseOn())
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
		else // �ۿ��� ��������
		{
			if (bLbtnAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
