#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:

public:
    CPlayer();
    ~CPlayer();

public:
    virtual void Render(HDC hdc);
    virtual void Update();

    CLONE(CPlayer);

private:
    void CreateMissile();   // 아무나 생성 못하게 private
};

