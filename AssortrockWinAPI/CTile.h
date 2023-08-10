#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture*   m_pTileTex;
    int         m_iImgIndex;   // 출력 위치

public:
    void SetTexture(CTexture* _pTex) { m_pTileTex = _pTex; }
    void AddImageIndex() { m_iImgIndex++; }

private:
    virtual void Update();
    virtual void Render(HDC hdc);
    CLONE(CTile);

public:
    CTile();
    ~CTile();
};

