#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

void CPlayer::Update()
{
	// �������� �����غ��� ���� ���� �����Ѱ� �ƴϴϱ� ���߿� setpos ���־�� �Ѵ�
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
