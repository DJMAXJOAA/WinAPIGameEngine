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
		CUI* pUI = (CUI*)vecUI[i];	// vector가 cobject형태로 받아왔으니 다운캐스팅
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

				// UI 버튼 위에서 눌렀었고, 그 뒤에 UI 버튼 위에서 뗐었으면 추가 호출
				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				pUI->m_bLbtnDown = false;
			}
		}
		else // 밖에서 떼졌을때
		{
			if (bLbtnAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
