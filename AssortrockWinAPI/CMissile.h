#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float   m_fTheta;   // �̵� ���� (����)
    Vec2    m_vDir; // ���� ���ư� ����(���⼺) -> ���� ����ȭ�� ���ؼ�

public:
    CMissile();
    ~CMissile();

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) { m_vDir = _vDir; m_vDir.Normalize(); }

public:
    virtual void Update();
    virtual void Render(HDC hdc);
};
