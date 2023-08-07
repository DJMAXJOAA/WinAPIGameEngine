#pragma once
#include "CObject.h"

class CMonster :
    public CObject
{
private:
    Vec2    m_vCenterPos;
    float   m_fSpeed;
    float   m_fMaxDistance;
    int     m_iDir; // -1, 1 (진행 방향 정보)

    int     m_iHP;

public:
    CMonster();
    ~CMonster();

public:
    float GetSpeed() { return m_fSpeed; }

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void Update();
};

