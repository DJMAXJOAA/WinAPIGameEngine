#include "pch.h"
#include "CCamera.h"
#include <random>

#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObject.h"

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(-1.0, 1.0);

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_bVibrating(false)
{
}

CCamera::~CCamera()
{
}

void CCamera::VibrateCamera()
{
	// 목표 진동횟수 채워지면
	if (m_iVibrate <= m_icurVibrate)
	{
		// 최종 위치로 맞춰주기 -> 화면 떨림 방지
		m_bVibrating = false;
		m_fAccTime = m_fTime;
	}
	else
	{
		if (m_fVTime <= m_fAccTime)
		{
			switch (m_iVibeCount)
			{
			case 0:
			{
				m_vCurLookAt = m_vPrevLookAt + m_vRandom * m_fSpeed * fDT;
				m_iVibeCount++;
				m_fAccTime = 0.f;
			}
			break;
			case 1:
			{
				m_vCurLookAt = m_vPrevLookAt + m_vRandom * -2.f * m_fSpeed * fDT;
				m_iVibeCount++;
				m_fAccTime = 0.f;
			}
			break;
			case 2:
			{
				m_vCurLookAt = m_vPrevLookAt + m_vRandom * m_fSpeed * fDT;
				m_iVibeCount = 0;
				m_icurVibrate++;
				m_fAccTime = 0.f;

				m_vRandom.x = distribution(generator);
				m_vRandom.y = distribution(generator);
				m_vRandom.Normalize();
			}
			break;
			}
		}
	}
}

void CCamera::SetLookAt(Vec2 _vLook)
{
	// 카메라 이동에 걸리는 시간이 정해져 있는 경우
	m_vLookAt = _vLook; 
	float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length(); 
	m_fSpeed = fMoveDist / m_fTime * 2.f;
	m_fAccTime = 0.f;
}

void CCamera::SetVibrateCamera(float _fPower, int _iVibrate, float _fTime)
{
	// 진동 세기, 진동 시간
	m_fVTime = _fTime;
	m_iVibrate = _iVibrate;
	m_icurVibrate = 0;
	m_iVibeCount = 0;
	m_fSpeed = _fPower * 100.f;

	m_vRandom.x = distribution(generator);
	m_vRandom.y = distribution(generator);
	m_vRandom.Normalize();

	m_bVibrating = true;
}

void CCamera::Update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_vLookAt.y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_vLookAt.y += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_vLookAt.x -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_vLookAt.x += 500.f * fDT;
	}

	// 화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값을 계산해준다
	CalDiif();
}

void CCamera::CalDiif()
{
	// 이전 LookAt과 현재 Look의 차이값 보정해서 현재의 LookAt 구하기
	m_fAccTime += fDT;
	m_fAccSpeed = m_fSpeed * (m_fAccTime / m_fTime); // 가속도 공식
	if (m_bVibrating)
	{
		VibrateCamera();
	}
	else
	{
		// 목표 시간이 넘었으면
		if (m_fTime <= m_fAccTime)
		{
			// 최종 위치로 맞춰주기 -> 화면 떨림 방지
			m_vCurLookAt = m_vLookAt;
		}
		else
		{
			Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * (m_fSpeed - m_fAccSpeed) * fDT;
		}
	}

	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
