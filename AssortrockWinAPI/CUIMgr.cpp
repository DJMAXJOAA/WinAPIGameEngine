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
	const vector<CObject*>& vecUI = pCurScnce->GetGroupObject(GROUP_TYPE::UI);	// 가장 최상위 부모들만 UI에 넣어져 있음

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];	// vector가 cobject형태로 받아왔으니 다운캐스팅

		pUI = GetTargetedUI(pUI);	// 제일 낮은 계층의 UI를 우선적으로 탐색한다
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

				// UI 버튼 위에서 눌렀었고, 그 뒤에 UI 버튼 위에서 뗐었으면 추가 호출
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

	//// 1. 부모 UI 포함해서, 모든 자식들을 검사한다 (자식이 여러명일수도, 부모가 여러명일수도 있음)
	CUI* pTargetUI = nullptr;
	
	// 항상 사용하는 컨테이너들이니까, 미리 정적변수로 선언해서 힙영역을 생성하고 지웠다가 반복할 필요 없게 설정해주기
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();	
	vecNoneTarget.clear();	// 판별 전에 정적 지역변수들 값 모두 초기화

	queue.push_back(_pParentUI);

	//// 2. BFS를 통해서, 가장 가까운 UI부터 타겟을 검사 (레벨 순회 방식)
	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI인지 확인한다=====================
		// 타겟 UI들중에 더 우선순위가 높은 기준으로 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			if (pTargetUI != nullptr)
			{
				// 자리 뺏긴애도 넣어주기
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
			// 타겟 아닌애들 미리 모아두고 걔네들만 따로 비활성화 처리
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
