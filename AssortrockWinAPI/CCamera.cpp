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
	// ��ǥ ����Ƚ�� ä������
	if (m_iVibrate <= m_icurVibrate)
	{
		// ���� ��ġ�� �����ֱ� -> ȭ�� ���� ����
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
	// ī�޶� �̵��� �ɸ��� �ð��� ������ �ִ� ���
	m_vLookAt = _vLook; 
	float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length(); 
	m_fSpeed = fMoveDist / m_fTime * 2.f;
	m_fAccTime = 0.f;
}

void CCamera::SetVibrateCamera(float _fPower, int _iVibrate, float _fTime)
{
	// ���� ����, ���� �ð�
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

	// ȭ�� �߾� ��ǥ�� ī�޶� LookAt ��ǥ���� ���̰��� ������ش�
	CalDiif();
}

void CCamera::CalDiif()
{
	// ���� LookAt�� ���� Look�� ���̰� �����ؼ� ������ LookAt ���ϱ�
	m_fAccTime += fDT;
	m_fAccSpeed = m_fSpeed * (m_fAccTime / m_fTime); // ���ӵ� ����
	if (m_bVibrating)
	{
		VibrateCamera();
	}
	else
	{
		// ��ǥ �ð��� �Ѿ�����
		if (m_fTime <= m_fAccTime)
		{
			// ���� ��ġ�� �����ֱ� -> ȭ�� ���� ����
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
