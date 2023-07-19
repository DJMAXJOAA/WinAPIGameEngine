#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

void CPlayer::Update()
{
	// 지역변수 수정해봤자 본인 값을 수정한게 아니니까 나중에 setpos 해주어야 한다
	Vec2 vPos = GetPos();

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		vPos.x -= 400.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		vPos.y -= 400.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		vPos.x += 400.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		vPos.y += 400.f * fDT;
	}

	SetPos(vPos);
}
