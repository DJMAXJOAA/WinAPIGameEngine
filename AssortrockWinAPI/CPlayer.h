#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex;

public:
    CPlayer();
    ~CPlayer();

public:
    virtual void Render(HDC hdc);
    virtual void Update();

private:
    void CreateMissile();
};

