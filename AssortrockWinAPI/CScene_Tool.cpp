#include "pch.h"
#include "CScene_Tool.h"

#include "CKeyMgr.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Update()
{
	CScene::Update();	// 부모쪽 함수를 이용할 수도 있음, 오버라이딩 한 이유는 +@ 하기 위해서

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Tool::Enter()
{
}

void CScene_Tool::Exit()
{
}
