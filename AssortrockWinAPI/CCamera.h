#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLookAt;		// ī�޶� ������ �ϴ� ��ǥ ī�޶� ��ġ (������Ʈ�� ��ġ�ʹ� �ٸ�, ������ǥ�� �����ǥ)
	Vec2		m_vCurLookAt;	// ���� �������� ���� �ִ� ��ġ
	Vec2		m_vPrevLookAt;	// ���� �������� ���� �ִ� ��ġ

	CObject*	m_pTargetObj;	// ī�޶� Ư�� ����� ����
	Vec2		m_vDiff;		// �ػ� �߽� ��ġ��, ī�޶� LookAt���� ���̰� ��갪

	float		m_fTime;		// ī�޶� Ÿ�� ��ġ���� �������� �ɸ��� ���� �ð�
	float		m_fSpeed;		// Ÿ���� ���󰡴� �ӵ�
	float		m_fAccSpeed;	// ��� ���ӵ�
	float		m_fAccTime;		// Ÿ�� ���� ���� �ð�

	Vec2		m_vRandom;		// ���� ���� ��ġ
	bool		m_bVibrating;	// ī�޶� ������
	float		m_fVTime;		// ���� ����
	int			m_iVibrate;		// ��ǥ ���� Ƚ��
	int			m_icurVibrate;	// ���� ���� Ƚ��
	int			m_iVibeCount;	// 1�ܰ�, 2�ܰ�, 3�ܰ�

public:
	CCamera();
	~CCamera();

public:
	bool IsVibrating() { return m_bVibrating; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	// ������Ʈ ���� ��ǥ�� ������ ��ǥ�� ���̸� ����������Ѵ�
	// ���콺 ��ġ ����Ҷ��� ������ ��ǥ �������� ����ϴϱ�, ������Ʈ�� �ݴ�� ���
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; } 

public:
	void VibrateCamera();

public:
	void SetLookAt(Vec2 _vLook);
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	void SetVibrateCamera(float _fPower, int _iVibrate, float _fTime);

public:
	void Update();

private:
	void CalDiif();
};
