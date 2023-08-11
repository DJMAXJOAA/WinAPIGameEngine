#include "pch.h"
#include "CScene_Tool.h"
#include "resource.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"

#include "CTile.h"
#include "CTexture.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::SetTileIndex()
{
	// ���� ��ġ�� �˾ƾߴ�

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInstance()->GetRealPos(vMousePos);

		// ������ Ư�� �ε����� �ٷ� �����ϱ� ����, ���� private ������ Ÿ�� ������ ����
		// �׷��� 2�� for������ ã�� �ʿ� ����, �ٷ� ������ �����ϰ� �Ѵ�
		int iTileX = GetTileX();
		int iTileY = GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		int iIndex = iRow * iTileX + iCol;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIndex])->AddImageIndex();
	}
}

void CScene_Tool::Update()
{
	CScene::Update();	// �θ��� �Լ��� �̿��� ���� ����, �������̵� �� ������ +@ �ϱ� ���ؼ�

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
	if (KEY_TAP(KEY::RBTN))
	{
		Vec2 vLookAt = CCamera::GetInstance()->GetRealPos(MOUSE_POS);
		CCamera::GetInstance()->SetLookAt(vLookAt);
	}

	SetTileIndex();
}

void CScene_Tool::Enter()
{
	CreateTile(5, 5);

	// UI �߰�
	Vec2 vResolution = CCore::GetInstance()->GetResolution();

	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 30.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	pPanelUI->AddChild(pBtnUI);

	// UI�� ���� UI�ϳ��� �� -> ��� ChildUI�� �Բ� ��
	AddObject(pPanelUI, GROUP_TYPE::UI);

	CCamera::GetInstance()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
}


// TILE COUNT WINDOW PROC
// �޴��� ��ü�� �� �������� Ȱ��ȭ�ǰ� �����ؾ� �Ѵ�
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			// ���� ���� �����´�
			CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();

			// �ٿ� ĳ���� -> ���� �� �� ���� �ƴ�
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}