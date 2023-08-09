#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HDC     m_hdc;
    HBITMAP m_hBit;
    BITMAP  m_bitInfo;

private:
    CTexture();
    virtual ~CTexture();

public:
    friend class CResMgr; // �����ڸ� private���� ����, ���� ���ҽ� �Ŵ����� ���ؼ��� ���� �����ϰ� ����

public:
    void Load(const wstring& _strFilePath);

public:
    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

public:
    HDC GetDC() { return m_hdc; }
};

